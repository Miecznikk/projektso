#!/bin/bash
line=$(head -n 1 "demon_pid.txt")
sudo kill -9 $line
rm $(pwd)/demon_pid.txt