#!/bin/bash
usage(){ cat << EOU

~/np/tests/go.sh 

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

tests=$(ls -1 N*.sh n*.sh | sort -r)

for t in $tests ; do 
    echo === ./$t 
    #eval ./$t
    eval ./$t > /dev/null
    #[ $? -ne 0 ] && echo non-zero RC : ABORT && break 
    [ $? -ne 0 ] && echo non-zero RC 
done 
  




