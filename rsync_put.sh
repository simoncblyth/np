#!/bin/bash -l
usage(){ cat << EOU
rsync_put.sh
=============

::

   cd ~/np         # on laptop
   ./rsync_put.sh  # copy repository to L7 

EOU
}

defarg="info_all"
arg=${1:-$defarg}

src=/Users/blyth/np/         ## for rsync a trailing slash on source directory means copy contents of this directory
#dst=L7:bes3/np
dst=L7:g/np
cmd="rsync -zarv --delete  $src $dst"

vars="BASH_SOURCE defarg arg src dst cmd"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/all}" != "$arg" ]; then
   date 
   echo $cmd
   eval $cmd
   [ $? -ne 0 ] && echo $BASH_SOURCE : all error && exit 1 
   date
fi 

