/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   Vector_test.cpp                                   :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: mamoussa <mamoussa@student.1337.ma>           +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2021/07/10 19:43:45 by mamoussa        #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2021/09/23 12:57:39 by moboustt         ###   ########.fr       */
/*                                                                                                  */
/* ************************************************************************************************ */

#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "../vector.hpp"

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

#if 1
void iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::Vector ---------*/
    ft::Vector<int> my_v(3, 4);
    ft::Vector<int>::iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Vector<int>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Vector<int>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::Vector<std::string> my_v(3, "hello");
        ft::Vector<std::string>::iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void const_iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector const_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::const_iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::Vector ---------*/
    ft::Vector<int> my_v(3, 4);
    ft::Vector<int>::const_iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Vector<int>::const_iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(*my_it == *(my_v.begin()) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::const_iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::Vector<std::string> my_v(3, "hello");
        ft::Vector<std::string>::const_iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_it[0] == *(my_v.begin())) && (&(my_it[0]) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::reverse_iterator<std::vector<int>::iterator> ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Vector<int> v(4, 5);
        ft::Vector<int>::reverse_iterator my_rit2(v.end());
        ft::Vector<int>::const_reverse_iterator c_it, c_ob(v.end());
        c_it = my_rit2;
        EQUAL(&(*my_rit2) == &(*c_it) && (&(*my_rit2) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(v.end() - 1)) && (&(*my_rit) == &(*(v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        std::reverse_iterator<std::vector<std::string>::iterator> rit(v.end());
        ft::reverse_iterator<std::vector<std::string>::iterator> my_rit(v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit[0] = 5) == 5) && (rit[0] == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit++);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit--);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        std::string res, my_res;
        std::reverse_iterator<std::vector<char>::iterator> start(v.end()), end(v.begin());
        ft::reverse_iterator<std::vector<char>::iterator> my_start(v.end()), my_end(v.begin());

        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_with_ft_vector(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator with ft::vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::reverse_iterator rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::Vector<int> my_v(3, 4);
    ft::Vector<int>::reverse_iterator my_rit(my_v.end()), my_rit1(my_v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Vector<int>::reverse_iterator ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(my_v.end() - 1)) && (&(*my_rit) == &(*(my_v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        ft::Vector<std::string> my_v(3, "hello");
        std::vector<std::string>::reverse_iterator rit(v.end());
        ft::Vector<std::string>::reverse_iterator my_rit(my_v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_rit[0] = 5) == 5);
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit++);
        ft::Vector<int>::reverse_iterator my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit--);
        ft::Vector<int>::reverse_iterator my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        ft::Vector<char> my_v(10);
        std::string res, my_res;
        std::vector<char>::reverse_iterator start(v.end()), end(v.begin());
        ft::Vector<char>::reverse_iterator my_start(my_v.end()), my_end(my_v.begin());
        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        size_t i = 0;
        for (ft::Vector<char>::iterator it = my_v.begin(); it != my_v.end(); ++it)
            *it = '0' + i++;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}
#endif

void vector_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " fill constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            start = get_time();
            std::vector<std::string> v(1e5, "fill constructor test");
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::Vector<std::string> my_v(1e5, "fill constructor test");
            ualarm(0, 0);
        }
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- fill tow vectors with a 10 strings ------*/
        ft::Vector<std::string> my_v(10, "fill constructor test");
        std::vector<std::string> v(10, "fill constructor test");
        /*---------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res;
        /*---------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::Vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::vector<std::string> v(1e5, "range constructor test");
            start = get_time();
            std::vector<std::string> v1(v.begin(), v.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::Vector<std::string> my_v(v.begin(), v.end());
            ualarm(0, 0);
        }
        /*-----------------------------------------------------------------------------------------------*/
        /*--------------- fill std::vector with 10 strings and ft::vector with range of iterators ------*/
        std::vector<std::string> v(10, "range constructor test");
        ft::Vector<std::string> my_v(10, "range constructor test");
        ft::Vector<std::string> my_v1(my_v.begin(), my_v.end()); // this one is to check if the range works with ft::vector
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res, my_res1;
        /*--------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::Vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;

        for (ft::Vector<std::string>::iterator it = my_v1.begin(); it != my_v1.end(); ++it) // fill my_res1 from ft::vector
            my_res1 += *it;
        EQUAL(res == my_res && my_res == my_res1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::vector<char> v(1e7, 'a');
            start = get_time();
            std::vector<char> copy_v(v);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * 20) : 20;

            ft::Vector<char> my_v(1e7, 'a');
            alarm(diff);
            ft::Vector<char> my_copy_v(my_v);
            alarm(0);
        }
        /*---------------------------------------------------------------------------------------------*/
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::Vector<char> v1(10, 'a');
        ft::Vector<char> copy_v(v1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::Vector<char>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<char>::iterator it = copy_v.begin(); it != copy_v.end(); ++it) // fill res from copy_v
            res1 += *it;
        EQUAL(res == res1);
    }
    /*------------------------------------------ = operator tests --------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 1 : test with equale size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string1");
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string1");
            ft::Vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string1");
        ft::Vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e4, "string1");
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e4, "string1");
            ft::Vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(20, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string1");
        ft::Vector<std::string> ft_v2(20, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string1");
            std::vector<std::string> v2(1e4, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string1");
            ft::Vector<std::string> ft_v2(1e4, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(20, "string1");
        ft::Vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1;
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1;
            ft::Vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1;
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1;
        ft::Vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            std::vector<std::string> v2;
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ft::Vector<std::string> ft_v2;
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> v2;
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> ft_v2;
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.begin();
            v1.end();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.begin();
            ft_v1.end();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;
        for (std::vector<std::string>::const_iterator rit = v2.begin(); rit != v2.end(); ++rit) // fill c_res from const v1
            c_res += *rit;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;
        for (ft::Vector<std::string>::const_iterator rit = ft_v2.begin(); rit != ft_v2.end(); ++rit) // fill c_ft_res from const ft_v1
            c_ft_res += *rit;

        EQUAL(res == ft_res && c_res == c_ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rbegin and rend methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.rbegin();
            v1.rend();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.rbegin();
            ft_v1.rend();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::reverse_iterator rit = v1.rbegin(); rit != v1.rend(); ++rit) // fill res from v1
            res += *rit;
        for (std::vector<std::string>::const_reverse_iterator rit = v2.rbegin(); rit != v2.rend(); ++rit) // fill c_res from const v1
            c_res += *rit;

        for (ft::Vector<std::string>::reverse_iterator rit = ft_v1.rbegin(); rit != ft_v1.rend(); ++rit) // fill ft_res from ft_v1
            ft_res += *rit;
        for (ft::Vector<std::string>::const_reverse_iterator rit = ft_v2.rbegin(); rit != ft_v2.rend(); ++rit) // fill c_ft_res from const ft_v1
            c_ft_res += *rit;

        EQUAL(res == ft_res && c_ft_res == c_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> ft_v2;
        ft::Vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::Vector<std::string> ft_v4(ft_v1);
        ft::Vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.size() == ft_v1.size() && v2.size() == ft_v2.size() && v3.size() == ft_v3.size() && v4.size() == ft_v4.size() && v5.size() == ft_v5.size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " capacity method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.capacity();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.capacity();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> ft_v2;
        ft::Vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::Vector<std::string> ft_v4(ft_v1);
        ft::Vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity() && v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity() && v5.capacity() == ft_v5.capacity());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " max_size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.max_size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.max_size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/

        std::vector<std::string> v1(10, "string");
        std::vector<int> v2;
        std::vector<double> v4;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<int> ft_v2;
        ft::Vector<double> ft_v4;
        /*----------------------------------------------------*/
        EQUAL(v1.max_size() == ft_v1.max_size() && v2.max_size() == ft_v2.max_size() && v4.max_size() == ft_v4.max_size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " resize method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*
             * test with n greater than vector capacity
             */
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(10, "string2");
            start = get_time();
            v1.resize(1e6);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(10, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.resize(1e6);
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*
             *	test with n lesser than capacity and greater than size
             */
            /*------------------ std::vectors ---------------------*/
            v1.resize(20);
            start = get_time();
            v1.resize(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft_v1.resize(20);
            ualarm(diff * 1e3, 0);
            ft_v1.resize(1e5);
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*
             * test with n lesser than capacity and lesser an size
             */
            /*------------------ std::vectors ---------------------*/
            v1.resize(100);
            start = get_time();
            v1.resize(50);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft_v1.resize(100);
            ualarm(diff * 1e3, 0);
            ft_v1.resize(50);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, s4, ft_s1, ft_s2, ft_s3, ft_s4;
        std::string sit1, sit2, sit3, ft_sit1, ft_sit2, ft_sit3; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, z4, ft_z1, ft_z2, ft_z3, ft_z4;
        size_t c1, c2, c3, c4, ft_c1, ft_c2, ft_c3, ft_c4;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::Vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        /*
         * test with n greater than vector capacity
         */
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        v1.resize(1e6, "hello");
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft_v1.resize(1e6, "hello");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s1 += *it;
        /*----------------------------------------------------*/
        /*
         *	test with n lesser than capacity and greater than size
         */
        /*------------------ std::vectors ---------------------*/
        v1.resize(20);
        valid_it = v1.begin();
        valid_eit = v1.end();
        v1.resize(1e5);
        /*------------------ ft::vectors ---------------------*/
        ft_v1.resize(20);
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        ft_v1.resize(1e5);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n lesser than capacity and lesser an size
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(50);
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(50);

        z3 = v1.size();
        ft_z3 = ft_v1.size();
        c3 = v1.capacity();
        ft_c3 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit2 += *valid_it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s3 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit2 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n = 0
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(0, "string4");
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(0, "string4");

        z4 = v1.size();
        ft_z4 = ft_v1.size();
        c4 = v1.capacity();
        ft_c4 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s4 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit3 += *valid_it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s4 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit3 += *ft_valid_it;
        /*----------------------------------------------------*/
        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3 && sit2 == ft_sit2) && (s4 == ft_s4 && z4 == ft_z4 && c4 == ft_c4 && sit3 == ft_sit3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.empty();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.empty();
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> v2;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<int> ft_v2;

        EQUAL(v1.empty() == ft_v1.empty() && v2.empty() == ft_v2.empty());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " reserve method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(10, "string2");
            start = get_time();
            v1.reserve(1e6);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(10, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.reserve(1e6);
            ualarm(0, 0);
        }
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        std::string sit1, ft_sit1; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::Vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        // bool to check if the function throw or not
        bool exec_throwed = false;
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<char> ft_v2;
        try
        {
            ft_v1.reserve(ft_v1.max_size() + 1);
        }
        catch (std::length_error const &e)
        {
            (void)e;
            exec_throwed = true;
        }
        v1.reserve(100);
        ft_v1.reserve(100);

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        ft_valid_it = ft_v1.begin();
        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_s1 += *ft_valid_it;

        valid_it = v1.begin();
        valid_eit = v1.end();
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        v1.reserve(50);
        ft_v1.reserve(50);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;

        v2.reserve(200);
        ft_v2.reserve(200);
        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();

        for (size_t i = 0; i < v2.size(); ++i)
            s3 += v2[i];

        for (ft::Vector<char>::iterator it = ft_v2.begin(); it != ft_v2.end(); ++it)
            ft_s3 += *it;

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3) && exec_throwed);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator[] method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1[1e6 - 1];
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1[1e6 - 1];
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;

        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1[i] = "other";
            s1 += v1[i];
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1[i] = "other";
            ft_s1 += ft_v1[i];
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2[i];

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2[i];

        EQUAL(s1 == ft_s1 && s2 == ft_s2);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " at method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.at(1e6 - 1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.at(1e6 - 1);
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;
        // bool to check if an exception is throwed
        bool exce_throwed = false;

        try
        {
            ft_v1.at(20);
        }
        catch (std::out_of_range const &e)
        {
            (void)e;
            exce_throwed = true;
        }
        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1.at(i) = "other";
            s1 += v1.at(i);
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1.at(i) = "other";
            ft_s1 += ft_v1.at(i);
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);
        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL(s1 == ft_s1 && s2 == ft_s2 && exce_throwed);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " front method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<int> const ft_v2(10, 9);

        v1.front() = "LEET";
        ft_v1.front() = "LEET";
        EQUAL(v1.front() == ft_v1.front() && v2.front() == ft_v2.front());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<int> const ft_v2(10, 9);

        v1.back() = "LEET";
        ft_v1.back() = "LEET";
        EQUAL(v1.back() == ft_v1.back() && v2.back() == ft_v2.back());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(fill) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.assign(1e6 + 1, "assign");
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.assign(1e6 + 1, "assign");
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<char> ft_v2;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v1.assign(20, "assign");
        ft_v1.assign(20, "assign");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s1 += ft_v1.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(10, "less");
        ft_v1.assign(10, "less");

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(20, 'h');
        ft_v2.assign(20, 'h');

        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(range) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            // std::vector<std::string>    v1(1e6, "string2");
            std::vector<std::string> v2(1e4, "string2");
            start = get_time();
            v2.assign(ft_v1.begin(), ft_v1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            // ft::Vector<std::string>    ft_v1(1e6, "string2");
            ft::Vector<std::string> ft_v2(1e4, "string2");
            ualarm(diff * 1e3, 0);
            ft_v2.assign(ft_v1.begin(), ft_v1.end());
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "less");
        std::vector<std::string> v2;
        std::vector<std::string> v3(10, "string2");
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(20, "less");
        ft::Vector<std::string> ft_v2;
        ft::Vector<std::string> ft_v3(10, "string2");
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v3.assign(v1.begin(), v1.end());
        ft_v3.assign(v1.begin(), v1.end());

        z1 = v3.size();
        c1 = v3.capacity();
        ft_z1 = ft_v3.size();
        ft_c1 = ft_v3.capacity();
        for (size_t i = 0; i < v3.size(); ++i)
            s1 += v3.at(i);

        for (size_t i = 0; i < ft_v3.size(); ++i)
            ft_s1 += ft_v3.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(v3.begin(), v3.end());
        ft_v1.assign(ft_v3.begin(), ft_v3.end());

        z2 = v1.size();
        c2 = v1.capacity();
        ft_z2 = ft_v1.size();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(v1.begin(), v1.end());
        ft_v2.assign(ft_v1.begin(), ft_v1.end());

        z3 = v2.size();
        c3 = v2.capacity();
        ft_z3 = ft_v2.size();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " push_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + the new element (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 1);
                start = get_time();
                v1.push_back("string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 1);
                ualarm(diff * 1e3, 0);
                ft_v1.push_back("string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + the new element (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.push_back("string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.push_back("string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        ft::Vector<std::string>::iterator ft_it;
        // test for an empty vector
        v.push_back("hello");
        ft_v.push_back("hello");
        ft_it = ft_v.begin();
        ft_it->length();

        z1 = v.size();
        c1 = v.capacity();
        ft_z1 = ft_v.size();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v.at(i);
        /*---------------------------------------------*/
        // test for a vector with capacity >= size + the new element
        v.reserve(30);
        ft_v.reserve(30);
        v.push_back("string");
        ft_v.push_back("string");
        v.push_back("string");
        ft_v.push_back("string");

        z2 = v.size();
        c2 = v.capacity();
        ft_z2 = ft_v.size();
        ft_c2 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s2 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s2 += ft_v.at(i);
        /*---------------------------------------------------------*/
        // test for a vector with capactiy < size + the new element
        for (size_t i = 0; i < 100; ++i)
            v.push_back("string");

        for (size_t i = 0; i < 100; ++i)
            ft_v.push_back("string");

        z3 = v.size();
        c3 = v.capacity();
        ft_z3 = ft_v.size();
        ft_c3 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s3 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s3 += ft_v.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " pop_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.pop_back();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.pop_back();
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v(20, "string");
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v(20, "string");
        /*
         * Strings to store the results
         */
        std::string s1, ft_s1;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, ft_z1;
        size_t c1, ft_c1;
        v.pop_back();
        ft_v.pop_back();
        z1 = v.size();
        ft_z1 = ft_v.size();
        c1 = v.capacity();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v[i];
        EQUAL(z1 == ft_z1 && c1 == ft_c1 && s1 == ft_s1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (single element) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + the new element (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 1);
                start = get_time();
                v1.insert(v1.begin() + 1e5, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 1);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + the new element (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, "string1");
                ualarm(0, 0);
            }
        }
        /*--------------------------------------------------------------------------------------*/
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        ft::Vector<std::string>::iterator ft_it;
        std::vector<std::string>::iterator it;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
            ft_it = ft_v.insert(ft_v.begin(), "hello");
            ft_it->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;

            it = v.insert(v.end(), "hello");
            ft_it = ft_v.insert(ft_v.end(), "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(30);
            ft_v.reserve(30);
            valid_it = ft_v.begin();
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (fill) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + n (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 200);
                start = get_time();
                v1.insert(v1.begin() + 1e5, 100, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 200);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, 100, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + n (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, 200, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, 200, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;
            v.insert(v.begin(), 100, "hello");
            ft_v.insert(ft_v.begin(), 100, "hello");
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;

            v.insert(v.end(), "hello");
            ft_v.insert(ft_v.end(), "hello");
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, 70, "hello");
            ft_v.insert(ft_v.begin() + 15, 70, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 100, "hello");
            ft_v.insert(ft_v.begin() + 10, 100, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 15, "hello");
            ft_v.insert(ft_v.begin() + 10, 15, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (range) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + n (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v(100, "hello");
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 200);
                start = get_time();
                v1.insert(v1.begin() + 1e5, v.begin(), v.end());
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(100, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 200);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, ft_v.begin(), ft_v.end());
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + n (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                ft::Vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, v.begin(), v.end());
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, v.begin(), v.end());
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v1(300, "string");
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;
            v.insert(v.begin(), v1.begin(), v1.end());
            ft_v.insert(ft_v.begin(), v1.begin(), v1.end());
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::Vector<std::string> v1(300, "string");
            ft::Vector<std::string> ft_v;

            v.insert(v.end(), v1.begin(), v1.end());
            ft_v.insert(ft_v.end(), v1.begin(), v1.end());
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v1(70, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 15, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            ft::Vector<std::string> v1(100, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v1(15, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (single element) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.erase(v1.begin() + 1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.erase(ft_v1.begin() + 1e5);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        std::vector<std::string> v(200, "hello");
        ft::Vector<std::string> ft_v(200, "hello");
        ft::Vector<std::string>::iterator valid_it;
        std::vector<std::string>::iterator it;
        ft::Vector<std::string>::iterator ft_it;
        valid_it = ft_v.begin() + 99;
        it = v.erase(v.begin() + 100);
        ft_it = ft_v.erase(ft_v.begin() + 100);
        ft_it->length();

        s = v.size();
        ft_s = ft_v.size();
        c = v.capacity();
        ft_c = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            str += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_str += ft_v[i];
        cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*(ft_v.begin() + 99))));
        cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        EQUAL(cond);
    }

    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (range) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.erase(v1.begin(), v1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.erase(ft_v1.begin(), ft_v1.end());
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        std::vector<std::string>::iterator it;
        ft::Vector<std::string>::iterator ft_it;
        /*
         * bool to store the comparison
         */
        bool cond;
        /*------------------ test 1: erase from the begin to end -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::Vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin(), v.end());
            ft_it = ft_v.erase(ft_v.begin(), ft_v.end());

            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 2: erase from the begin to begin + 70 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::Vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin(), v.begin() + 70);
            ft_it = ft_v.erase(ft_v.begin(), ft_v.begin() + 70);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        /*------------------ test 3: erase from the begin + 60 to end -------------------*/

        {
            std::vector<std::string> v(100, "hello");
            ft::Vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 60, v.end());
            ft_it = ft_v.erase(ft_v.begin() + 60, ft_v.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 4: erase from the begin + 20 to end - 30 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::Vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 20, v.end() - 30);
            ft_it = ft_v.erase(ft_v.begin() + 20, ft_v.end() - 30);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v.swap(v1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v(1e6, "string");
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v.swap(ft_v1);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        ft::Vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(50, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            start = get_time();
            v.clear();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v.clear();
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            ft::Vector<std::string> ft_v(200, "hello");

            v.clear();
            ft_v.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " get_allocator method "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(200, "hello");
        ft::Vector<std::string> ft_v(200, "hello");

        EQUAL(v.get_allocator().max_size() == ft_v.get_allocator().max_size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator== "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v == v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v == ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v == v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v == ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator!= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v != v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v != ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v != v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v != ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator< "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v < v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v < ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v < v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v < ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator<= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v <= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v <= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v <= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v <= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator> "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v > v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v > ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v > v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v > ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator>= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v >= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e6, "string");
                ft::Vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v >= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v >= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::Vector<std::string> ft_v(1e5, "hello");
                ft::Vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v >= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = ((v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::Vector<int> ft_v(50, 5);
            ft::Vector<int> ft_v1(100, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::Vector<int> ft_v(100, 5);
            ft::Vector<int> ft_v1(50, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            swap(v, v1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v(1e6, "string");
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            swap(ft_v, ft_v1);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        ft::Vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::Vector<std::string> ft_v(200, "hello");
            ft::Vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::Vector<std::string> ft_v(50, "hello");
            ft::Vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
} // vec_end

void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}

int main(void)
{
    std::cout << RED << "________________________________________________________________________________________________________" << std::endl;
    std::cout << RED << "**** The test is taking so much time to test the all cases and the time complexity of each method ****" << std::endl;
    std::cout << RED << "--------------------------------------------------------------------------------------------------------" << RESET << std::endl;
    signal(SIGALRM, alarm_handler);
    iterator_tests();
    const_iterator_tests();
    reverse_iterator_tests();
    reverse_iterator_with_ft_vector();
    vector_tests();
    return 0;
}