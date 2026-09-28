#!/usr/bin/env bash
usage(){ cat << EOU

~/np/tests/NP_MakePSum_test.sh

EOU
}


name=NP_MakePSum_test
script=${name}.py

defarg="info_gcc_run_pdb"
arg=${1:-$defarg}

cd $(dirname $(realpath $BASH_SOURCE))

tmp=/tmp/$USER/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name


vv="BASH_SOURCE PWD name defarg arg tmp TMP FOLD bin script"

if [[ "$arg" =~ info ]]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ gcc ]]; then
    gcc $name.cc -std=c++17 -lstdc++ -I.. -g -lm -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - gcc FAIL && exit 1
fi

if [[ "$arg" =~ run ]]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - run FAIL && exit 1
fi

if [[ "$arg" =~ pdb ]]; then
    PYTHONPATH=$HOME ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE - pdb FAIL && exit 1
fi

if [[ "$arg" =~ ana ]]; then
    PYTHONPATH=$HOME ${PYTHON:-python} $script
    [ $? -ne 0 ] && echo $BASH_SOURCE - ana FAIL && exit 1
fi

exit 0



