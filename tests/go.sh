#!/bin/bash 

tests=$(ls -1 *Test.cc *test.cc)

for t in $tests ; do 
    echo === $t 
    cmd=$(head -1 $t | perl -ne 'm,//(.*)$, && print "$1\n" ' -)
    echo $cmd  
    #eval $cmd 
    eval $cmd > /dev/null
    [ $? -ne 0 ] && echo non-zero RC : ABORT && break 
done 
  




