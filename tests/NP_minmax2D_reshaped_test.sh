#!/bin/bash -l 
usage(){ cat << EOU
NP_minmax2D_reshaped_test.sh
==============================

::

    ~/np/tests/NP_minmax2D_reshaped_test.sh

EOU
}

name=NP_minmax2D_reshaped_test

cd $(dirname $(realpath $BASH_SOURCE))

gcc $name.cc -std=c++11 -I.. -lstdc++ -o /tmp/$name && /tmp/$name


