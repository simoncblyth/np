#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_Make_ellipsis_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
name=NP_Make_ellipsis_test
script=$name.py 

export FOLD=/tmp/$name 

defarg=ana
arg=${1:-$defarg}

if [ "${arg/pdb}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 1 
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 2 
fi 

exit 0 


