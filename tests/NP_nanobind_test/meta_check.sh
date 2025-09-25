#!/usr/bin/env bash
usage(){ cat << EOU

~/np/tests/NP_nanobind_test/meta_check.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=meta_check

export FOLD=/tmp/$USER/np/NP_nanobind_test/meta_check
mkdir -p $FOLD

script=$name.py

${IPYTHON:-ipython} --pdb -i $script



