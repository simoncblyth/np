#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_DescMetaKVS_ranges_test.sh

EOU
}



cd $(dirname $(realpath $BASH_SOURCE))

name=NP_DescMetaKVS_ranges_test
bin=/tmp/$name

gcc $name.cc -g -Wall -std=c++11 -lstdc++ -I.. -o $bin  && $bin 



