#!/bin/bash -l 

name=NP_LoadOptional_test

 gcc $name.cc -std=c++11 -lstdc++ -I.. -DWITH_VERBOSE  -o /tmp/$name && /tmp/$name

