#!/bin/bash -l

name=NPMakeICDFTest 

mkdir -p /tmp/$name 

gcc $name.cc -std=c++11 -I.. -DDEBUG  -lstdc++ -o /tmp/$name/$name 
[ $? -ne 0 ] && echo compile fail && exit 1 

/tmp/$name/$name 
[ $? -ne 0 ] && echo run fail && exit 2 

ipython -i $name.py
[ $? -ne 0 ] && echo ana fail && exit 3

exit 0 

