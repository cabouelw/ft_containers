#!/bin/sh
rm a.out
c++ -Wall -Wextra -Werror -std=c++98  test.cpp
./a.out