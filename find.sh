#!/usr/bin/env bash

DIR=$(dirname $(realpath $BASH_SOURCE))
script=$DIR/find.py
${IPYTHON:-ipython} $script


