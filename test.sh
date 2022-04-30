#!/bin/bash
mkdir ~/test3
mkdir ~/test3/folder1
mkdir ~/test3/folder2
mkdir ~/test4
touch ~/test3/plik.txt
touch ~/test3/plik2.txt
truncate -s 12M ~/test3/ostechnix.txt
truncate -s 14M ~/test3/ciezkiplik.txt
touch ~/test4/plikdousuniecia.txt
touch ~/test4/plikdousuniecia2.txt
truncate -s 20M ~/test4/ciezkiplikdousuniecia.txt
echo "this is a line" > ~/test3/plik.txt
echo "this is a line" > ~/test3/plik2.txt
make program
./program -r -s ~/test3 -d ~/test4

