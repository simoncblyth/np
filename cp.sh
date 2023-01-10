#!/bin/bash -l 

names="NP.hh NPU.hh NPFold.h"

for name in $names ; do 
    cmd="diff $name ~/opticks/sysrap/$name"
    echo $cmd
    eval $cmd
    rc=$?
    echo rc $rc 

    if [ $rc -ne 0 ]; then 
       cpcmd="cp $name ~/opticks/sysrap/$name"
       read -p "Enter YES to proceed with : $cpcmd : "  ans
       if [ "$ans" == "YES" ]; then
           eval $cpcmd
       fi 
    fi 
done 

