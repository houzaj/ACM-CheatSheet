!/bin/bash

rm ./$1
g++ $1.cpp -std=gnu++14 -Wall -o $1
./$1
