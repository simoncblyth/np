#!/bin/bash -l 

sysrap_names="np.h NP.hh NPU.hh NPFold.h NPX.h"


for name in $sysrap_names ; do 
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


ana_names="npmeta.py"

for name in $ana_names ; do 
    cmd="diff $name ~/opticks/ana/$name"
    echo $cmd
    eval $cmd
    rc=$?
    echo rc $rc 

    if [ $rc -ne 0 ]; then 
       cpcmd="cp $name ~/opticks/ana/$name"
       read -p "Enter YES to proceed with : $cpcmd : "  ans
       if [ "$ans" == "YES" ]; then
           eval $cpcmd
       fi 
    fi 
done 




