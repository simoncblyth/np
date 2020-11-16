#!/bin/bash -l

tt=$(ls -1 np_server.cc np_client.cc)

for t in $tt ; do 
    echo === $t 
    cmd=$(head -1 $t | perl -ne 'm,//(.*)&&(.*)$, && print "$1\n" ' -)  # skip && invokation 
    echo $cmd  
    #eval $cmd 
    eval $cmd > /dev/null
    [ $? -ne 0 ] && echo non-zero RC : ABORT && break 
done 
  




