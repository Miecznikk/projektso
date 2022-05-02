#!/bin/bash
make time_test
truncate -s 14M "$(pwd)/ciezkiplik.txt"
./time_test $(pwd)/ciezkiplik.txt ~/ciezkiplik.txt
rm $(pwd)/ciezkiplik.txt
