#!/bin/bash -l 

name=NPMakeTest 
mkdir -p /tmp/$name 

gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name 
[ $? -ne 0 ] && echo $msg compile error && exit 1 

if [ -n "$DEBUG" ]; then 
    lldb__ /tmp/$name/$name
else
    /tmp/$name/$name
fi 
[ $? -ne 0 ] && echo $msg run error && exit 2

exit 0 

