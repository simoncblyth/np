#!/bin/bash -l 

name=NPX_ArrayFromEnumMap_test 

export FOLD=/tmp/$name 
mkdir -p $FOLD 

gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name 

$FOLD/$name

${IPYTHON:-ipython} --pdb -i $name.py 




