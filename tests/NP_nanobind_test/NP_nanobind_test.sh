#!/usr/bin/env bash

usage(){ cat << EOU
NP_nanobind_test.sh
=====================

Started from sources ~/env/tools/nanobind_check
and zeta build in /usr/local/env/nanobind_check

::

    cd ~/env/tools/nanobind_check

    ./nanobind_check.sh venv
    ./nanobind_check.sh info
    ./nanobind_check.sh build
    ./nanobind_check.sh pdb

Using *uv* with *cmake* to build a python-C++ nanobind
module requires candlewax and sealing tape of this script ?

EOU
}


name=NP_nanobind_test
script=main.py


defarg="venv_info_build_pdb"
arg=${1:-$defarg}

vv="BASH_SOURCE PWD"
tt="uv cmake python python3 ipython"

cd $(dirname $(realpath $BASH_SOURCE))

if [ "${arg/venv}" != "$arg" ]; then
    if [ ! -d ".venv" ]; then
        echo ".venv\n" >> .gitignore
        uv init
        uv add nanobind numpy ipython
    else
         echo $BASH_SOURCE .venv exists already
    fi
fi

[ ! -d ".venv" ] && echo $BASH_SOURCE .venv MISSING && exit 1
source .venv/bin/activate


if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
    for t in $tt ; do printf "which %30s     : %s\n" "$t" "$(which $t)" ; done
    for t in $tt ; do printf "%30s --version : %s\n" "$t" "$($t --version)" ; done
    python -m nanobind --cmake_dir
fi


if [ "${arg/build}" != "$arg" ]; then

    if [ ! -d "build" ]; then
        echo "build\n" >> .gitignore
        cmake -S . -B build
        [ $? -ne 0 ] && echo $BASH_SOURCE - config error && exit 1
    fi
    cmake --build build
    [ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then
   PYTHONPATH=build ipython --pdb -i $script
fi

if [ "${arg/clean}" != "$arg" ]; then
   rm -rf build
   rm -rf .venv
   rm uv.lock  #  too long and unreadable to be comfortable adding to repo
fi

exit 0

