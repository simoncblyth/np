#!/bin/bash -l 
usage(){ cat << EOU
NP_Concatenate_test.sh
========================

::
 
   ~/np/tests/NP_Concatenate_test.sh 


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NP_Concatenate_test

export FOLD=/tmp/$name
mkdir -p $FOLD
bin=$FOLD/$name
script=$name.py 

defarg=info_build_run_ana
arg=${1:-$defarg}

vars="BASH_SOURCE FOLD bin name" 

if [ "${arg/info}" != "$arg" ]; then 
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi

if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++11 -lstdc++ -I.. -g -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1  
fi

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1  
fi

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} -i --pdb $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1  
fi





