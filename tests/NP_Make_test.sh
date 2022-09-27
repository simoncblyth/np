#!/bin/bash -l 
msg="=== $BASH_SOURCE :"
name=NP_Make_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name 
[ $? -ne 0 ] && echo $msg build error && exit 1 

/tmp/$name/$name 
[ $? -ne 0 ] && echo $msg run error && exit 2

${IPYTHON:-ipython} --pdb -i $name.py 
[ $? -ne 0 ] && echo $msg ana error && exit 3

exit 0 

