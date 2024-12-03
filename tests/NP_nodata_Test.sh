#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_nodata_Test.sh

EOU
}

name=NP_nodata_Test
FOLD=${TMP:-/tmp/$USER/opticks}/$name
bin=$FOLD/$name
mkdir -p $FOLD

cd $(dirname $(realpath $BASH_SOURCE))

#opt=-DWITH_VERBOSE
opt=

gcc $name.cc -I.. -std=c++11 -lstdc++ $opt -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 


cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001
[ $? -ne 0 ] && echo NON EXISTING DIR && exit 0 

for npy in $(ls -1 *.npy) ; do $bin  $npy ; done 
for npy in $(ls -1 *.npy) ; do $bin @$npy ; done 

[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

exit 0 

