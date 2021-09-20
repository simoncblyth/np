#!/bin/bash -l 

name=NPpdomainTest 

mkdir -p /tmp/$name  
mkdir -p /tmp/$name/3d 

gcc $name.cc -DDEBUG -I.. -std=c++11 -lstdc++ -o /tmp/$name/$name 
[ $? -ne 0 ] && echo compile FAIL && exit 1 

/tmp/$name/$name 
[ $? -ne 0 ] && echo run FAIL && exit 2

ipython -i $name.py 
[ $? -ne 0 ] && echo ana FAIL && exit 3

exit 0 

