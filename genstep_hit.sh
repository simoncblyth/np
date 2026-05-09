#!/usr/bin/env bash

DIR=$(dirname $(realpath $BASH_SOURCE))
script=$DIR/genstep_hit.py
${IPYTHON:-ipython} $script


