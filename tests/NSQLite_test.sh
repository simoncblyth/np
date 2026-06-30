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
sql=~/j/opticks_monitoring/opticks_monitoring_schema.sql
evt=/data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first_sreport/evsmry.npy
bin=/tmp/$name

defarg="info_gcc_run1_check1"
arg=${1:-$defarg}

vv="BASH_SOURCE PWD name db sql evt bin defarg arg"

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

if [ "${arg/run0}" != "$arg" ]; then
   $bin $db
   [ $? -ne 0 ] && echo $BASH_SOURCE - run0 error && exit 2
fi

if [ "${arg/run1}" != "$arg" ]; then
   $bin $db $sql $evt
   [ $? -ne 0 ] && echo $BASH_SOURCE - run1 error && exit 2
fi

if [ "${arg/check0}" != "$arg" ]; then
   echo "select * from student ;" | sqlite3 -table $db
   [ $? -ne 0 ] && echo $BASH_SOURCE - check error && exit 2
fi

if [ "${arg/check1}" != "$arg" ]; then
   echo "select * from opticks_events ;" | sqlite3 -table $db
   [ $? -ne 0 ] && echo $BASH_SOURCE - check error && exit 2
fi





if [ "${arg/query}" != "$arg" ]; then
   sqlite3 $db
fi 

exit 0




