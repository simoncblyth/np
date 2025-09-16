#!/usr/bin/env bash

usage(){ cat << EOU

fastapi_nanobind_check.sh
===========================

~/np/tests/fastapi_nanobind_check/fastapi_nanobind_check.sh


EOU
}


cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$PWD

defarg="venv_build_pdb"
arg=${1:-$defarg}


if [ "${arg/curl}" != "$arg" ]; then
    curl -X POST "http://127.0.0.1:8000/process" \
      -H "Content-Type: application/json" \
      -d '{"data": [1.0, 2.0, 3.0]}'

    echo $BASH_SOURCE - curl rc $?
    exit 0
fi


if [ "${arg/clean}" != "$arg" ]; then
   rm -rf .venv
   rm -rf build
   rm -rf __pycache__
   rm -f uv.lock
   rm -f pyproject.toml
   rm -f my_ext.pyi
   rm -f my_ext.so
   rm -f README.md
fi

if [ "${arg/venv}" != "$arg" ]; then
    if [ ! -d ".venv" ]; then
        echo ".venv\n" >> .gitignore
        uv init
        uv add nanobind numpy ipython fastapi[standard]
    else
         echo $BASH_SOURCE .venv exists already
    fi
fi

[ ! -d ".venv" ] && echo $BASH_SOURCE .venv MISSING && exit 1
source .venv/bin/activate


if [ "${arg/build}" != "$arg" ]; then
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    make
    cp my_ext.cpython-*.so ../my_ext.so
    cp my_ext.pyi ../my_ext.pyi
    cd $SDIR
fi


cd $SDIR
if [ "${arg/run}" != "$arg" ]; then

   which fastapi
   fastapi dev main.py
   [ $? -ne 0 ] && echo $BASH_SOURCE - failed to fastapi dev && exit 2
fi



if [ "${arg/pdb}" != "$arg" ]; then
   PYTHONPATH=build ipython --pdb -i main.py
fi

exit 0

