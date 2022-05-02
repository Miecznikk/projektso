#!/bin/bash
DIR=~/test3
if [ -d "$DIR" ]; then
    echo "$DIR exists."
else 
    mkdir $DIR
fi


DIR2=~/test3/folder1
if [ -d "$DIR2" ]; then
    echo "$DIR2 exists."
else
    mkdir $DIR2
fi

DIR3=~/test3/folder2
if [ -d "$DIR3" ]; then
    echo "$DIR3 exists."
else
    mkdir $DIR3
fi

DIR4=~/test4
if [ -d "$DIR4" ]; then
    echo "$DI4 exists."
else
    mkdir $DIR4
fi

FILE=~/test3/plik.txt
if [ -f "$FILE" ]; then
    echo "$FILE exists."
else 
    touch $FILE
    echo "this is a line" > $FILE
fi

FILE2=~/test3/plik2.txt
if [ -f "$FILE2" ]; then
    echo "$FILE2 exists."
else 
    touch FILE2
    echo "this is a line" > $FILE2
fi

FILE3=~/test3/ostechnix.txt
if [ -f "$FILE3" ]; then
    echo "$FILE3 exists."
else 
    truncate -s 12M $FILE3
fi

FILE4=~/test3/ciezkiplik.txt
if [ -f "$FILE4" ]; then
    echo "$FILE4 exists."
else 
    truncate -s 14M $FILE4
fi

FILE5=~/test4/plikdousuniecia.txt
if [ -f "$FILE5" ]; then
    echo "$FILE5 exists."
else 
    touch $FILE5
fi

FILE6=~/test3/ciezkipliktestsize.txt
if [ -f "$FILE6" ]; then
    echo "$FILE6 exists."
else 
    truncate -s 20M $FILE6
fi

FILE7=~/test3/folder1/testowy.txt
if [ -f "$FILE7" ]; then
    echo "$FILE7 exists."
else 
    truncate -s 25M $FILE7
fi

FILE8=~/test3/folder2/testowy2.txt
if [ -f "$FILE8" ]; then
    echo "$FILE8 exists."
else 
    truncate -s 11M $FILE8
fi

echo "Update Demon"
make program
echo "Start Program Demon"
echo "Parameters -R Time-60s Weight=16 MB"
./program -r -s ~/test3 -d ~/test4 -t 60 -w 16