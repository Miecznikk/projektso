#!/bin/bash
filename='demon_pid.txt'
n=1
while read line; do
echo "Line No. $n : $line"
sudo kill -9 $line
done < $filename