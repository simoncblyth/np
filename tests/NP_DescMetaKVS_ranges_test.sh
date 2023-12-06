#!/bin/bash -l 


cd $(dirname $(realpath $BASH_SOURCE))
name=NP_DescMetaKVS_ranges_test
bin=/tmp/$name

gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o $bin  && $bin 

#dbg__ $bin


