#!/bin/bash
usage(){ cat << EOU
NP_minmax2D_reshaped_test.sh
==============================

::

    ~/np/tests/NP_minmax2D_reshaped_test.sh

EOU
}

name=NP_minmax2D_reshaped_test

bin=/tmp/$name

cd $(dirname $(realpath $BASH_SOURCE))

gcc $name.cc -std=c++17 -I.. -Wall -lstdc++ -o $bin && $bin




