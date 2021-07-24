#!/bin/bash 

name=NPCombineTest 
mkdir -p /tmp/$name 

gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name/$name 
[ $? -ne 0 ] && echo compile error && exit 1 

/tmp/$name/$name
[ $? -ne 0 ] && echo run error && exit 2

ipython -i $name.py 
[ $? -ne 0 ] && echo ana error && exit 3


exit 0 

