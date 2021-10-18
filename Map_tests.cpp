//
// Created by moboustt on 19/8/2021.
//

// you should include your path to this files

#include "../map/Map.hpp"       // your Map path.
#include "../vector/Vector.hpp" // your Vector path.
#include "../utility/pair.hpp"  // path to ft::pair.
// #include "map-test-helper.hpp"
#include <map>

#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 4 // the ft::Map methods can be slower up to std::map methods * TIME_FAC (MAX 20)

typedef std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> iter_def;
typedef ft::pair<ft::Map<int, std::string>::iterator, ft::Map<int, std::string>::iterator> ft_iter_def;
typedef std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> const_iter_def;
typedef ft::pair<ft::Map<int, std::string>::const_iterator, ft::Map<int, std::string>::const_iterator> ft_const_iter_def;

#define TEST_CASE(fn)                                                                                                             \
    cout << GREEN << "\t======================================================================================" << RESET << endl; \
    cout << endl;                                                                                                                 \
    cout << BLUE << "\t   Running " << #fn << " ... \t\t\t\t\t\t" << RESET << std::endl;                                          \
    fn();                                                                                                                         \
    cout << endl;                                                                                                                 \
    cout << GREEN << "\t======================================================================================" << RESET << endl;
using namespace std;

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

bool testMapConstructors()
{
    bool cond;
    std::map<char, int> first;
    ft::Map<char, int> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    std::map<char, int> copy(first);
    ft::Map<char, int> m_copy(m_first);

    cond = first.size() == m_first.size() && compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    std::map<char, int> second(first.begin(), first.end());
    ft::Map<char, int> m_second(m_first.begin(), m_first.end());

    cond = cond && second.size() == m_second.size() && compareMaps(second.begin(), second.end(), m_second.begin(), m_second.end());
    std::map<char, int> third(second);
    ft::Map<char, int> m_third(m_second);

    cond = cond && third.size() == m_third.size() && compareMaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    std::map<char, int, classcomp> fourth;  // class as Compare
    ft::Map<char, int, classcomp> m_fourth; // class as Compare

    cond = fourth.size() == m_fourth.size() && cond && compareMaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    ft::Map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    cond = fifth.size() == m_fifth.size() && cond && compareMaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    first = std::map<char, int>();
    m_first = ft::Map<char, int>();

    cond = copy.size() == m_copy.size() && cond && compareMaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    return cond;
}

void iterator_tests(void)
{
    /*------------ std::map ---------*/
    std::map<int, char> m;
    std::map<int, char>::iterator it, it1;

    ft::Map<int, char> my_m;
    ft::Map<int, char>::iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
        m.insert(std::make_pair(i, static_cast<char>(i + 97)));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());
    /*----------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Map<int, char>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Map<int, char>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((((*my_it).second = '6') == '6') && ((*my_it).first == ((*my_m.begin()).first)));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::map-------------------- */
        std::map<int, std::string> m;
        ft::Map<int, std::string> my_m;

        for (int i = 0; i < 5; ++i)
        {
            m.insert(std::make_pair(13, "HELLO"));
            my_m.insert(ft::make_pair(13, "HELLO"));
        }

        ft::Map<int, std::string>::iterator my_it = my_m.begin();
        std::map<int, std::string>::iterator it = m.begin();
        /*---------------------------------------------- */
        EQUAL(it->second.length() == my_it->second.length());
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
                ;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            for (ft::Map<int, std::string>::iterator it = ft_m.begin(); it != ft_m.end(); ++it)
                ;
            ualarm(0, 0);
        }
        bool cond(false);
        {
            int res(0);
            int myints[] = {12, 82, 37, 64, 15};
            ft::Map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            for (ft::Map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
                res += it->first;
            cond = res == 210;
        }
        {
            int res(0), tmp;
            int myints[] = {12, 82, 37, 64, 15};
            ft::Map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            ft::Map<int, int>::iterator it = m.begin(), eit = --m.end();
            tmp = eit->first;
            m.erase(eit);
            for (; it != m.end(); ++it)
                res += it->first;
            cond = cond && (res == (210 - tmp));
        }
        ++my_it; // I incremented here to make sure that the object changes
        EQUAL(*my_it == *my_it1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            std::map<int, std::string>::iterator it = --m.end();
            for (; it != m.begin(); --it)
                ;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::Map<int, std::string>::iterator ft_it = --ft_m.end();
            for (; ft_it != ft_m.begin(); --ft_it)
                ;
            ualarm(0, 0);
        }
        int res(0);
        {
            int myints[] = {12, 82, 37, 64, 15};
            ft::Map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            ft::Map<int, int>::iterator it = --m.end();
            for (;; --it)
            {
                if (it == m.begin())
                {
                    res += it->first;
                    break;
                }
                res += it->first;
            }
        }
        --my_it; // I decremented here to make sure that the object changes
        EQUAL(*my_it != *my_it1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void const_iterator_tests(void)
{
    /*------------ std::map ---------*/
    std::map<int, char> m;
    std::map<int, char>::const_iterator it, it1;

    ft::Map<int, char> my_m;
    ft::Map<int, char>::const_iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
        m.insert(std::make_pair(i, static_cast<char>(i + 97)));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());
    /*----------------------------------*/

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Map<int, char>::const_iterator ob(my_it);
        EQUAL(*my_it == *ob);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::map-------------------- */
        std::map<int, std::string> m;
        ft::Map<int, std::string> my_m;

        for (int i = 0; i < 5; ++i)
        {
            m.insert(std::make_pair(13, "HELLO"));
            my_m.insert(ft::make_pair(13, "HELLO"));
        }

        ft::Map<int, std::string>::iterator my_it = my_m.begin();
        std::map<int, std::string>::iterator it = m.begin();
        /*---------------------------------------------- */
        EQUAL(it->second.length() == my_it->second.length());
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(*my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(*my_it != *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void reverse_iterator_tests(void)
{
    /*------------ std::reverse_iterator ---------*/
    std::map<int, char> m;
    for (int i = 0; i < 1e2; i++)
        m.insert(std::make_pair(i, 'A'));

    std::reverse_iterator<std::map<int, char>::iterator> rit(m.end()), rit_1(--m.end());

    ft::reverse_iterator<std::map<int, char>::iterator> my_rit(m.end()), my_rit1(--m.end());
    /*----------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::reverse_iterator<std::map<int, char>::iterator> ob(my_rit);
        EQUAL(*my_rit == *ob);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::Map<int, char> my_m;
        for (int i = 0; i < 1e2; i++)
            my_m.insert(ft::make_pair(i, 'A'));

        ft::Map<int, char>::reverse_iterator my_rit2(my_m.end());
        ft::Map<int, char>::const_reverse_iterator c_it, c_ob(my_m.end());
        c_it = my_rit2;
        EQUAL(my_rit2->first == c_it->first && my_rit2->first == c_ob->first);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit->first == (rit_1.base()->first)) && (my_rit->first == my_rit1.base()->first));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit->first == (--m.end())->first) && ((my_rit->first) == ((--m.end())->first))) && ((rit->first == (--m.end())->first) && ((rit->first) == ((--m.end())->first))));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((((*my_rit).first == (*(--m.end())).first) && (((*my_rit).first) == ((*(--m.end())).first))) && (((*rit).first == (*(--m.end())).first) && ((*(rit)).first) == ((*(--m.end())).first)));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((my_rit->first == (--my_rit1)->first) && (rit->first == (--rit_1)->first));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::map<int, char>::iterator> tmp(rit++);
        ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit++);
        EQUAL(tmp->first == (--rit)->first && my_tmp->first == (--my_rit)->first);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        rit++;
        my_rit++;
        std::reverse_iterator<std::map<int, char>::iterator> tmp(rit--);
        ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit--);
        EQUAL(tmp->first == (++rit)->first && my_tmp->first == (++my_rit)->first);
    }
}

void testConstructors()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            start = get_time();
            std::map<int, std::string> m;
            for (int i = 0; i < 1e6; ++i)
                m.insert(std::make_pair(i, "fill constructor test"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);

            ft::Map<int, std::string> my_m;
            for (int i = 0; i < 1e6; ++i)
                my_m.insert(ft::make_pair(i, "fill constructor test"));
            ualarm(0, 0);
        }
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- fill tow vectors with a 10 strings ------*/
        ft::Map<int, std::string> my_m;
        std::map<int, std::string> m;
        for (int i = 0; i < 10; i++)
        {
            m.insert(std::make_pair(i, "Hello"));
            my_m.insert(ft::make_pair(i, "Hello"));
        }

        /*---------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res;
        /*---------------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it) // fill res from std::map
            res += it->second;
        for (ft::Map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it) // fill res from std::map
            my_res += it->second;
        EQUAL(res == my_res);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m;
            ft::Map<int, std::string> my_m;

            for (size_t i = 0; i < 1e6; i++)
            {
                m.insert(std::make_pair(i, "range constructor test"));
                my_m.insert(ft::make_pair(i, "range constructor test"));
            }

            start = get_time();
            std::map<int, std::string> m1(m.begin(), m.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::Map<int, std::string> my_m1(my_m.begin(), my_m.end());
            ualarm(0, 0);
        }
        /*-----------------------------------------------------------------------------------------------*/
        /*--------------- fill std::map with 10 strings and ft::Map with range of iterators ------*/
        std::map<int, std::string> m;
        ft::Map<int, std::string> my_m;
        for (size_t i = 0; i < 10; i++)
        {
            m.insert(std::make_pair(i, "range constructor test"));
            my_m.insert(ft::make_pair(i, "range constructor test"));
        }

        ft::Map<int, std::string> my_m1(my_m.begin(), my_m.end()); // this one is to check if the range works with ft::Map
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res, my_res1;
        int sum(0), my_sum(0), my_sum1(0);
        /*--------------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
        { // fill res from std::map
            res += it->second;
            sum += it->first;
        }

        for (ft::Map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it)
        { // fill my_res from ft::Map
            my_res += it->second;
            my_sum += it->first;
        }

        for (ft::Map<int, std::string>::iterator it = my_m1.begin(); it != my_m1.end(); ++it)
        { // fill my_res1 from ft::Map
            my_res1 += it->second;
            my_sum1 += it->first;
        }
        EQUAL(res == my_res && my_res == my_res1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, char> m;
            ft::Map<int, char> my_m;

            for (size_t i = 0; i < 1e3; i++)
            {
                m.insert(std::make_pair(i, 'X'));
                my_m.insert(ft::make_pair(i, 'X'));
            }

            start = get_time();
            std::map<int, char> copy_m(m);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * 20) : 20;

            alarm(diff);
            ft::Map<int, char> my_copy_m(my_m);
            alarm(0);
        }
        /*---------------------------------------------------------------------------------------------*/
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::Map<int, char> m1;
        for (int i = 0; i < 10; i++)
            m1.insert(ft::make_pair(i, 'a'));
        ft::Map<int, char> copy_m(m1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::Map<int, char>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, char>::iterator it = copy_m.begin(); it != copy_m.end(); ++it) // fill res from copy_m
            res1 += it->second;
        EQUAL(res == res1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " Constructors with costum compare "
              << "] --------------------]\t\t\033[0m";
    EQUAL(testMapConstructors());
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= (lhs.size = rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::Map<int, std::string> ft_m1;
            ft::Map<int, std::string> ft_m2;
            for (int i = 0; i < 1e6; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                m2.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string1"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;
        for (int i = 0; i < 10; ++i)
        {
            m1.insert(std::make_pair(i, "string1"));
            m2.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }

        m1 = m2;
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->first;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->first;

        EQUAL(res == ft_res);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= deep copy "
              << "] --------------------]\t\t\033[0m";
    {
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m2;
        ft::Map<int, std::string> ft_m1;
        for (int i = 0; i < 1e4; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }

        m1 = m2;
        ft_m1 = ft_m2;
        m2.begin()->second = "hello";
        ft_m2.begin()->second = "hello";

        EQUAL((m1.begin()->second != m2.begin()->second) && (ft_m1.begin()->second != ft_m2.begin()->second));
    }

    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::map ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::Map<int, std::string> ft_m1;
            ft::Map<int, std::string> ft_m2;

            for (int i = 0; i < 1e4; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }

            for (int i = 0; i < 1e6; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;
        for(size_t i = 0; i < 100; ++i)
        {
            m2.insert(std::make_pair(i, "value"));
            ft_m2.insert(ft::make_pair(i, "value"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::Map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::map ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::Map<int, std::string> ft_m1;
            ft::Map<int, std::string> ft_m2;

            for (int i = 0; i < 1e4; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }

            for (int i = 0; i < 1e2; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }
            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;

        for (int i = 0; i < 20; ++i)
        {
            m1.insert(std::make_pair(i, "string1"));
            ft_m1.insert(ft::make_pair(i, "string1"));
        }

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::Map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::Map<int, std::string> ft_m1;
            ft::Map<int, std::string> ft_m2;

            for (int i = 0; i < 1e6; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::Map ---------------------*/

        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::nap ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::Map<int, std::string> ft_m1;
            ft::Map<int, std::string> ft_m2;

            for (int i = 0; i < 1e6; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }
            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::Map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
}

void testIterators()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.begin();
            m1.end();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.begin();
            ft_m1.end();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1;
        ft::Map<int, std::string> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> const m2(m1.begin(), m1.end());
        ft::Map<int, std::string> const ft_m2(ft_m1.begin(), ft_m1.end());

        /*-----------------------------------------------------*/
        /*------------------ ft::Maps ---------------------*/
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;
        for (std::map<int, std::string>::const_iterator rit = m2.begin(); rit != m2.end(); ++rit) // fill c_res from const m1
            c_res += rit->second;

        for (ft::Map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;
        for (ft::Map<int, std::string>::const_iterator rit = ft_m2.begin(); rit != ft_m2.end(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += rit->second;
        
        int arr[] = {12, 82, 37, 64, 15};
        ft::Map<int, int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(ft::make_pair(arr[i], i));
        ft::Map<int, int>::iterator eit = end_test.end();
        eit--;
        EQUAL(res == ft_res && c_res == c_ft_res && eit->first == 82);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rbegin and rend methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.rbegin();
            m1.rend();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.rbegin();
            ft_m1.rend();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1;
        ft::Map<int, std::string> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> const m2(m1.rbegin(), m1.rend());
        ft::Map<int, std::string> const ft_m2(ft_m1.rbegin(), ft_m1.rend());

        /*-----------------------------------------------------*/
        /*------------------ ft::Maps ---------------------*/
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it) // fill res from m1
            res += it->second;
        for (std::map<int, std::string>::const_reverse_iterator rit = m2.rbegin(); rit != m2.rend(); ++rit) // fill c_res from const m1
            c_res += rit->second;

        for (ft::Map<int, std::string>::reverse_iterator it = ft_m1.rbegin(); it != ft_m1.rend(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;
        for (ft::Map<int, std::string>::const_reverse_iterator rit = ft_m2.rbegin(); rit != ft_m2.rend(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += rit->second;
        int arr[] = {12, 82, 37, 64, 15};
        ft::Map<int, int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(ft::make_pair(arr[i], i));
        ft::Map<int, int>::reverse_iterator rit = end_test.rend();
        rit--;
        EQUAL(res == ft_res && c_res == c_ft_res && rit->first == 12);
    }
}

void testCapacityMethods()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1; // fill constructor
        ft::Map<int, std::string> ft_m1;
        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> m2;                         // empty constructor
        std::map<int, std::string> m3(m1.begin(), m1.end());   // range constructor with normal iterators
        std::map<int, std::string> m4(m3);                     // copy constructor
        std::map<int, std::string> m5(m1.rbegin(), m1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::Maps ---------------------*/
        ft::Map<int, std::string> ft_m2;
        ft::Map<int, std::string> ft_m3(ft_m1.begin(), ft_m1.end());
        ft::Map<int, std::string> ft_m4(ft_m1);
        ft::Map<int, std::string> ft_m5(ft_m1.rbegin(), ft_m1.rend());
        /*----------------------------------------------------*/
        EQUAL(m1.size() == ft_m1.size() && m2.size() == ft_m2.size() && m3.size() == ft_m3.size() && m5.size() == ft_m5.size() && m4.size() == ft_m4.size());
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
    {
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m1;
        ft::Map<int, std::string> ft_m2;
        m1[0] = "stringsrtring";
        ft_m1[0] = "stringsrtring";
        EQUAL(m1.empty() == ft_m1.empty() && m2.empty() == ft_m2.empty());
    }
}

void testElementAccess()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator [] "
              << "] --------------------]\t\t\033[0m";
    {
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;

            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }
            start = get_time();
            m1[1e6] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6] = "string";
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            start = get_time();
            m1[1e6 - 100] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = "string";
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            start = get_time();
            m1[1e6 - 100] = m1[1e5];
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = ft_m1[1e5];
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        std::map<char, std::string> m;
        ft::Map<char, std::string> ft_m;

        m['a'] = "an element";
        m['b'] = "another element";
        m['c'] = m['b'];
        m['a'] = "test";

        ft_m['a'] = "an element";
        ft_m['b'] = "another element";
        ft_m['c'] = ft_m['b'];
        ft_m['a'] = "test";

        EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
    }
}

void testModifiers()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(false);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;

            start = get_time();
            for (size_t i = 0; i < 1e6; i++)
                m1.insert(std::make_pair(i, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            for (size_t i = 0; i < 1e6; i++)
                ft_m1.insert(ft::make_pair(i, "string2"));

            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m_range;
            ft::Map<int, std::string> ft_m_range;

            start = get_time();
            m_range.insert(m1.begin(), m1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m_range.insert(ft_m1.begin(), ft_m1.end());
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;

            start = get_time();
            m1.insert(std::make_pair(1e9, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.insert(ft::make_pair(1e9, "string2"));
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        std::map<char, int> m;
        ft::Map<char, int> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

        // first insert function version (single parameter):
        m.insert(std::pair<char, int>('a', 100));
        m.insert(std::pair<char, int>('z', 200));

        ft_m.insert(ft::pair<char, int>('a', 100));
        ft_m.insert(ft::pair<char, int>('z', 200));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        std::pair<std::map<char, int>::iterator, bool> ret;
        ft::pair<ft::Map<char, int>::iterator, bool> ft_ret;

        ret = m.insert(std::pair<char, int>('z', 500));
        ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

        cond = cond && ret.second == ft_ret.second;

        // second insert function version (with hint position):
        std::map<char, int>::iterator it = m.begin();
        ft::Map<char, int>::iterator ft_it = ft_m.begin();
        m.insert(it, std::pair<char, int>('b', 300));
        m.insert(it, std::pair<char, int>('c', 400));

        ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
        ft_m.insert(ft_it, ft::pair<char, int>('c', 400));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        // third insert function version (range insertion):
        std::map<char, int> anothermap;
        ft::Map<char, int> ft_anothermap;
        anothermap.insert(m.begin(), m.find('c'));
        ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));
        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

        cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method "
              << "] --------------------]\t\t\033[0m";

    {
        bool cond(false);
        // erasing all the elements in the map;
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.erase(m1.begin(), m1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.erase(ft_m1.begin(), ft_m1.end());
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        std::map<char, int> m;
        ft::Map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::Map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        /* ---------- Testing some edge cases ---------- */

        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m2;

        for (size_t i = 0; i < 1e5; i++)
        {
            m2.insert(std::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string1"));
        }

        std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
        ft::Map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        m2.erase(it2->first);
        ft_m2.erase(ft_it2->first);

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        std::map<int, std::string> m3;
        ft::Map<int, std::string> ft_m3;
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        for (size_t i = 0; i < 1e6; i++)
        {
            m3.insert(std::make_pair(i, "string1"));
            ft_m3.insert(ft::make_pair(i, "string1"));
        }

        for (size_t i = 0; i < 1e6; ++i)
        {
            int n = distr(generator);
            int ret1 = m3.erase(n);
            int ret2 = ft_m3.erase(n);

            if (ret1 != ret2)
            {
                cond = false;
                break;
            }
        }

        if (!m3.empty())
        {
            m3.erase(m3.begin(), m3.end());
            m3.erase(m3.begin(), m3.end());
        }
        if (!ft_m3.empty())
        {
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
        }
        cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
              << "] --------------------]\t\t\033[0m";

    {
        {
            time_t start, end, diff;

            /* ------------------ a > b ------------------ */
            std::map<int, std::string> m1, m2;
            ft::Map<int, std::string> ft_m1, ft_m2;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.swap(m2);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.swap(ft_m2);
            ualarm(0, 0);
            /*----------------------------------------------------*/

            /* ------------------ a and b are not empty ------------------ */
            for (size_t i = 0; i < 1e4; i++)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.swap(m2);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.swap(ft_m2);
            ualarm(0, 0);
            /*----------------------------------------------------*/

            /* ------------------ a == b ------------------ */
            m1 = m2 = std::map<int, std::string>();
            ft_m1 = ft_m2 = ft::Map<int, std::string>();
            start = get_time();
            m2.swap(m1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m2.swap(ft_m1);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        bool cond = false;
        std::map<char, int> foo, bar;
        ft::Map<char, int> ft_foo, ft_bar;

        foo['x'] = 100;
        foo['y'] = 200;

        ft_foo['x'] = 100;
        ft_foo['y'] = 200;

        cond = foo.size() == ft_foo.size() && bar.size() == ft_bar.size();

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        ft_bar['a'] = 11;
        ft_bar['b'] = 22;
        ft_bar['c'] = 33;

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        foo.swap(bar);
        ft_foo.swap(ft_bar);

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        std::map<std::string, std::string, std::greater<std::string> > m1, m2;
        ft::Map<std::string, std::string, std::greater<std::string> > ft_m1, ft_m2;

        m1["γ"] = "gamma";
        m1["β"] = "beta";
        m1["α"] = "alpha";
        m1["γ"] = "gamma";

        m2["ε"] = "eplsilon";
        m2["δ"] = "delta";
        m2["ε"] = "epsilon";

        ft_m1["γ"] = "gamma";
        ft_m1["β"] = "beta";
        ft_m1["α"] = "alpha";
        ft_m1["γ"] = "gamma";

        ft_m2["ε"] = "eplsilon";
        ft_m2["δ"] = "delta";
        ft_m2["ε"] = "epsilon";

        const std::pair<std::string, std::string> &ref = *(m1.begin());
        const std::map<std::string, std::string, std::greater<std::string> >::iterator iter = std::next(m1.begin());
        const ft::pair<std::string, std::string> &ft_ref = *(ft_m1.begin());
        const ft::Map<std::string, std::string, std::greater<std::string> >::iterator ft_iter = std::next(ft_m1.begin());

        // std::cout << "──────── before swap ────────\n"
        //           << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
        //           << "\niter: " << *iter << '\n';

        cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        m1.swap(m2);
        ft_m1.swap(ft_m2);

        // _---------------_ << ──────── after swap ──────── >> _---------------_

        cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
              << "] --------------------]\t\t\033[0m";

    {
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.clear();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.clear();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        bool cond(false);
        std::map<char, int> m;
        ft::Map<char, int> ft_m;

        m['x'] = 100;
        m['y'] = 200;
        m['z'] = 300;

        ft_m['x'] = 100;
        ft_m['y'] = 200;
        ft_m['z'] = 300;

        cond = m.size() == ft_m.size();

        m.clear();
        ft_m.clear();

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m['a'] = 1101;
        m['b'] = 2202;
        ft_m['a'] = 1101;
        ft_m['b'] = 2202;

        cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m = std::map<char, int>();
        ft_m = ft::Map<char, int>();

        m.clear();
        ft_m.clear();

        cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond);
    }
}

struct ModCmp
{
    bool operator()(const int lhs, const int rhs) const
    {
        return (lhs % 97) < (rhs % 97);
    }
};

void testObservers()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " key_comp method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(true);
        std::map<int, int> m;
        ft::Map<int, int> ft_m;
        std::map<int, int>::key_compare comp = m.key_comp();
        ft::Map<int, int>::key_compare mycomp = ft_m.key_comp();

        for (size_t i = 0; i < 1e2; i++)
        {
            m.insert(std::make_pair(i, -1));
            ft_m.insert(ft::make_pair(i, -1));
        }

        int highest = m.rbegin()->first;       // key value of last element
        int ft_highest = ft_m.rbegin()->first; // key value of last element

        std::map<int, int>::iterator it = m.begin();
        ft::Map<int, int>::iterator ft_it = ft_m.begin();
        do
        {
            if (!(it->first == ft_it->first && it->second == ft_it->second))
            {
                cond = false;
                break;
            }

        } while (comp((*it++).first, highest) && mycomp((*ft_it++).first, ft_highest));
        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " value_comp method "
              << "] --------------------]\t\t\033[0m";
    {
        int sum(0);
        int s_key(0);
        ft::Map<char, int> mymap;

        mymap['x'] = 1001;
        mymap['y'] = 2002;
        mymap['z'] = 3003;

        ft::pair<char, int> highest = *mymap.rbegin(); // last element

        ft::Map<char, int>::iterator it = mymap.begin();
        do
        {
            sum += it->second;
            s_key += it->first;
        } while (mymap.value_comp()(*it++, highest));

        EQUAL(sum == 6006 && s_key == 363);
    }
}
void testNonMemberSwap()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " non-member swap method "
              << "] --------------------]\t\t\033[0m";
    {
        int res(0), ft_res(0), key_res(0), ft_key_res(0);
        ft::Map<char, int> foo, bar;

        foo['x'] = 100;
        foo['y'] = 200;

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        swap(foo, bar);

        for (ft::Map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
        {
            res += it->second;
            key_res += it->first;
        }

        for (ft::Map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
        {
            ft_res += it->second;
            ft_key_res += it->first;
        }
        EQUAL((res == 66) && (ft_res = 300) && (key_res == ('a' + 'b' + 'c')) && (ft_key_res == ('x' + 'y')));
    }
}

void testOperations()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " find method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(true);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();

            for (size_t i = 1e1; i < 1e5; i += 10)
                m1.find(i);

            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            for (size_t i = 1e1; i < 1e5; i += 10)
                ft_m1.find(i);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        std::map<int, std::string> m1;
        ft::Map<int, std::string> ft_m1;
        std::map<int, std::string>::iterator it;
        ft::Map<int, std::string>::iterator ft_it;

        for (size_t i = 0; i < 1e6; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        for (size_t i = 0; i < 1e6; i++)
        {
            int n = distr(generator);
            it = m1.find(n);
            ft_it = ft_m1.find(n);
            if (it == m1.end() && ft_it == ft_m1.end())
                continue;
            if (it == m1.end() && ft_it != ft_m1.end())
            {
                cond = false;
                break;
            }
            else
            {
                vec.push_back(it->first);
                ft_vec.push_back(ft_it->first);
            }
        }

        std::map<char, int> m;
        ft::Map<char, int> ft_m;
        std::map<char, int>::iterator it2;
        ft::Map<char, int>::iterator ft_it2;

        m['a'] = 50;
        m['b'] = 100;
        m['c'] = 150;
        m['d'] = 200;

        ft_m['a'] = 50;
        ft_m['b'] = 100;
        ft_m['c'] = 150;
        ft_m['d'] = 200;

        it2 = m.find('b');
        ft_it2 = ft_m.find('b');

        cond = cond && it2->first == ft_it2->first && it2->second == ft_it2->second;

        if (it2 != m.end())
            m.erase(it2);
        if (ft_it2 != ft_m.end())
            ft_m.erase(ft_it2);

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond && vec == ft_vec);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " count method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            bool res, ft_res;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.count(1e6 - 10);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.count(1e6 - 10);
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::Map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        cond = (cond && (m.count(65) == ft_m.count(65) && m.count(300) == ft_m.count(300)));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " lower_bound method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            int res, ft_res;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.lower_bound(1e5)->first;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.lower_bound(1e5)->first;
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::Map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::Map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (cond && (m.lower_bound(15)->first == ft_m.lower_bound(15)->first));
        cond = (cond && (m.lower_bound(65)->first == ft_m.lower_bound(65)->first));
        cond = (cond && (m.lower_bound(63)->first == ft_m.lower_bound(63)->first));
        cond = (cond && (m.lower_bound(120)->first == ft_m.lower_bound(120)->first));
        cond = (cond && (m.lower_bound(70)->first == ft_m.lower_bound(70)->first));

        cond = (cond && (c_m.lower_bound(15)->first == c_ft_m.lower_bound(15)->first));
        cond = (cond && (c_m.lower_bound(65)->first == c_ft_m.lower_bound(65)->first));
        cond = (cond && (c_m.lower_bound(63)->first == c_ft_m.lower_bound(63)->first));
        cond = (cond && (c_m.lower_bound(120)->first == c_ft_m.lower_bound(120)->first));
        cond = (cond && (c_m.lower_bound(70)->first == c_ft_m.lower_bound(70)->first));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " upper_bound method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            int res, ft_res;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.upper_bound(1e5)->first;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.upper_bound(1e5)->first;
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::Map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::Map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (cond && (m.upper_bound(15)->first == ft_m.upper_bound(15)->first));
        cond = (cond && (m.upper_bound(65)->first == ft_m.upper_bound(65)->first));
        cond = (cond && (m.upper_bound(63)->first == ft_m.upper_bound(63)->first));
        cond = (cond && (m.upper_bound(120)->first == ft_m.upper_bound(120)->first));
        cond = (cond && (m.upper_bound(70)->first == ft_m.upper_bound(70)->first));
        cond = (cond && (m.upper_bound(150)->first == ft_m.upper_bound(150)->first));

        cond = (cond && (c_m.upper_bound(15)->first == c_ft_m.upper_bound(15)->first));
        cond = (cond && (c_m.upper_bound(65)->first == c_ft_m.upper_bound(65)->first));
        cond = (cond && (c_m.upper_bound(63)->first == c_ft_m.upper_bound(63)->first));
        cond = (cond && (c_m.upper_bound(120)->first == c_ft_m.upper_bound(120)->first));
        cond = (cond && (c_m.upper_bound(70)->first == c_ft_m.upper_bound(70)->first));
        cond = (cond && (c_m.upper_bound(150)->first == c_ft_m.upper_bound(150)->first));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " equal_range method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            iter_def res;
            ft_iter_def ft_res;

            std::map<int, std::string> m;
            ft::Map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.equal_range(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.equal_range(1e5);
            ualarm(0, 0);
            cond = (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first);
        }
        iter_def res;
        ft_iter_def ft_res;
        const_iter_def c_res;
        ft_const_iter_def ft_c_res;
        std::map<int, std::string> m;
        ft::Map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::Map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());

        res = m.equal_range(15);
        ft_res = ft_m.equal_range(15);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(65);
        ft_res = ft_m.equal_range(65);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(63);
        ft_res = ft_m.equal_range(63);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(120);
        ft_res = ft_m.equal_range(120);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(70);
        ft_res = ft_m.equal_range(70);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(150);
        ft_res = ft_m.equal_range(150);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));

        c_res = c_m.equal_range(15);
        ft_c_res = c_ft_m.equal_range(15);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(65);
        ft_c_res = c_ft_m.equal_range(65);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(63);
        ft_c_res = c_ft_m.equal_range(63);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(120);
        ft_c_res = c_ft_m.equal_range(120);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(70);
        ft_c_res = c_ft_m.equal_range(70);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(150);
        ft_c_res = c_ft_m.equal_range(150);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        EQUAL(cond);
    }
}

void testAllocatorMethodes()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " get_allocator method "
              << "] --------------------]\t\t\033[0m";
    {
        int psize;
        ft::Map<char, int> mymap;
        ft::pair<const char, int> *p;

        // allocate an array of 5 elements using mymap's allocator:
        p = mymap.get_allocator().allocate(5);

        psize = sizeof(std::map<char, int>::value_type) * 5;
        EQUAL(psize == 40);
        mymap.get_allocator().deallocate(p, 5);
    }
}
void testRetionalOperators()
{

    /* ---------------  pretty simple tests --------------- */
    std::map<char, int> foo, bar;
    ft::Map<char, int> ft_foo, ft_bar;
    bool res;
    bool ft_res;
    foo['a'] = 100;
    foo['b'] = 200;
    bar['a'] = 10;
    bar['z'] = 1000;

    ft_foo['a'] = 100;
    ft_foo['b'] = 200;
    ft_bar['a'] = 10;
    ft_bar['z'] = 1000;

    std::map<int, std::string> m, m1;
    ft::Map<int, std::string> ft_m, ft_m1;
    for (size_t i = 0; i < 1e6; ++i)
    {
        m.insert(std::make_pair(i, "value"));
        ft_m.insert(ft::make_pair(i, "value"));
    }
    for (size_t i = 0; i < 1e6; ++i)
    {
        m1.insert(std::make_pair(i + 1, "value1"));
        ft_m1.insert(ft::make_pair(i + 1, "value1"));
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator == "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m == m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m == ft_m1;
        ualarm(0, 0);
    }

    EQUAL(((foo == bar) == (ft_foo == ft_bar)) && res == ft_res);

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator != "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m != m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m != ft_m1;
        ualarm(0, 0);
    }
    EQUAL((foo != bar) == (ft_foo != ft_bar) && res == ft_res);

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator > "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m > m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m > ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo > bar) == (ft_foo > ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator >= "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m >= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m >= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo >= bar) == (ft_foo >= ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator < "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m < m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m < ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo < bar) == (ft_foo < ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator <= "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m <= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m <= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo <= bar) == (ft_foo <= ft_bar)) && (res == ft_res));
}

void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}

int main()
{

    std::cout << RED << "________________________________________________________________________________________________________" << std::endl;
    std::cout << RED << "**** The test is taking so much time to test the all cases and the time complexity of each method ****" << std::endl;
    std::cout << RED << "--------------------------------------------------------------------------------------------------------" << RESET << std::endl;
    signal(SIGALRM, alarm_handler);

    std::cout << YELLOW << "Testing Iterators;" << RESET << std::endl;
    TEST_CASE(iterator_tests);
    TEST_CASE(const_iterator_tests);
    TEST_CASE(reverse_iterator_tests);
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
    TEST_CASE(testConstructors);
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Iterator Methods;" << RESET << std::endl;
    TEST_CASE(testIterators);
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Capacity Methods;" << RESET << std::endl;
    TEST_CASE(testCapacityMethods)
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Access Element Methods; " << RESET << std::endl;
    TEST_CASE(testElementAccess);
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Modifiers Methods;" << RESET << std::endl;
    TEST_CASE(testModifiers)
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Observers Methods;" << RESET << std::endl;
    TEST_CASE(testObservers)
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Operations Methods;" << RESET << std::endl;
    TEST_CASE(testOperations)
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Allocator Methods;" << RESET << std::endl;
    TEST_CASE(testAllocatorMethodes)
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Retional Operators; " << RESET << std::endl;
    TEST_CASE(testRetionalOperators);
    std::cout << std::endl;

    std::cout << YELLOW << "Testing Non-Member Swap  ; " << RESET << std::endl;
    TEST_CASE(testNonMemberSwap);
    std::cout << std::endl;
    return 0;
}
