#!/bin/bash -l 

name=NP_ReadKV_test 

gcc $name.cc -g -std=c++11 -lstdc++ -I.. -o /tmp/$name && lldb__ /tmp/$name


