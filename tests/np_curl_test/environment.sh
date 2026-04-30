#!/bin/bash

opt_source() {
    if [ -f "$1" ]; then
        source "$1"
    else
        echo "$BASH_SOURCE $FUNCNAME - SKIP NON-EXISTING : $1"
    fi
}

#opt_source /usr/local/ExternalLibs/openssl/openssl-3.2.0/bashrc
#opt_source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc
opt_source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Python/3.11.10/bashrc
opt_source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/python-numpy/1.26.4/bashrc

