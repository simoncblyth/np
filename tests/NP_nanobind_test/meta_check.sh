#!/usr/bin/env bash

name=meta_check

export FOLD=/tmp/$USER/np/NP_nanobind_test/meta_check
mkdir -p $FOLD

script=$name.py

${IPYTHON:-ipython} --pdb -i $script



