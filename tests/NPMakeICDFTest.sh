#!/bin/bash -l

name=NPMakeICDFTest 

if [ "$1" == "py" ]; then 

    ipython -i $name.py
    [ $? -ne 0 ] && echo ana fail && exit 3

else
    mkdir -p /tmp/$name 

    #opt=-DDEBUG
    opt=
    gcc $name.cc -std=c++11 -I.. $opt  -lstdc++ -o /tmp/$name/$name 
    [ $? -ne 0 ] && echo compile fail && exit 1 

    /tmp/$name/$name 
    [ $? -ne 0 ] && echo run fail && exit 2 

    ipython -i $name.py
    [ $? -ne 0 ] && echo ana fail && exit 3
fi 

exit 0 

