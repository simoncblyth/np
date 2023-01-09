#!/bin/bash -l

name=NP_set_meta_get_meta_test 

mkdir -p /tmp/$name 

gcc $name.cc -std=c++11 -lstdc++ -I.. -DDEBUG -o /tmp/$name/$name && /tmp/$name/$name

