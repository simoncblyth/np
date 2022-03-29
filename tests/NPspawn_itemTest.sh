#!/bin/bash -l 

msg="=== $BASH_SOURCE :"
name=NPspawn_itemTest 

mkdir -p /tmp/$name 

gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name 
[ $? -ne 0 ] && echo $msg compile error && exit 1 

/tmp/$name/$name
[ $? -ne 0 ] && echo $msg run error && exit 2 

FOLD=/tmp/$name ipython -i $name.py 
[ $? -ne 0 ] && echo $msg ana error && exit 3

exit 0 


