# ************************************************************************************************** #
#                                                                                                    #
#                                                         :::   ::::::::   ::::::::  :::::::::::     #
#    Makefile                                          :+:+:  :+:    :+: :+:    :+: :+:     :+:      #
#                                                       +:+         +:+        +:+        +:+        #
#    By: mamoussa <mamoussa@student.1337.ma>           +#+      +#++:      +#++:        +#+          #
#                                                     +#+         +#+        +#+      +#+            #
#    Created: Invalid date        by                 #+#  #+#    #+# #+#    #+#     #+#              #
#    Updated: 2021/08/10 17:14:13 by mamoussa     ####### ########   ########      ###.ma            #
#                                                                                                    #
# ************************************************************************************************** #

COMPILER = clang++
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror -fsanitize=address -g3
FLAGS = --std=c++98 -Wall -Wextra -Werror

vector_tle:
	@$(COMPILER) $(FLAGS_DEBUG)	Vector_tests_tle.cpp -o vector.out 

vector:
	@$(COMPILER) $(FLAGS)	Vector_tests.cpp -o vector.out 

map:
	@$(COMPILER) $(FLAGS)	Map_tests.cpp -o map.out 

stack:
	@$(COMPILER) $(FLAGS)	Stack_tests.cpp -o stack.out 

set:
	@$(COMPILER) $(FLAGS)	Set_tests.cpp -o set.out 
clean:
	rm -f vector.out map.out stack.out set.out
