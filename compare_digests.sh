#!/usr/bin/env bash

DIR=$(dirname $(realpath $BASH_SOURCE))
script=$DIR/compare_digests.py
${IPYTHON:-ipython} $script $*


