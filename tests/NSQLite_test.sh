#!/bin/bash

usage(){ cat << EOU
NSQLite_test.sh
================

~/np/tests/NSQLite_test.sh

::

    ~/np/tests/NSQLite_test.sh query

    SQLite version 3.34.1 2021-01-20 14:10:07
    Enter ".help" for usage hints.
    sqlite> .mode table
    sqlite> select * from student ;
    +----+------------+-----------+-------------------+
    | ID | FIRST_NAME | LAST_NAME |       EMAIL       |
    +----+------------+-----------+-------------------+
    | 1  | John       | Doe       | john@doe.com      |
    | 2  | Peter      | Griffin   | peter@griffin.com |
    | 3  | Homer      | Simpson   | homer@simpson.com |
    | 4  | Peter      | Parker    | peter@batcave.com |
    +----+------------+-----------+-------------------+
    sqlite> 

EOU
}

name=NSQLite_test
db=/tmp/db.sqlite3
bin=/tmp/$name

defarg="info_gcc_run_check"
arg=${1:-$defarg}

vv="BASH_SOURCE PWD name db bin defarg arg"

cd $(dirname $(realpath $BASH_SOURCE))

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/gcc}" != "$arg" ]; then
    gcc $name.cc -I.. -std=c++17 -lstdc++ -lsqlite3 -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - gcc error && exit 1
fi

if [ "${arg/clean}" != "$arg" ]; then
   rm -f $db
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin $db
   [ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2
fi

if [ "${arg/check}" != "$arg" ]; then
   echo "select * from student ;" | sqlite3 -table $db
   [ $? -ne 0 ] && echo $BASH_SOURCE - check error && exit 2
fi

if [ "${arg/query}" != "$arg" ]; then
   sqlite3 $db
fi 

exit 0




