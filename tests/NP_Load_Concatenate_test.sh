#!/bin/bash -l 


name=NP_Load_Concatenate_test 


in_fold=/tmp/$name
out_fold=/tmp/$name/concat

export IN_FOLD=$in_fold
export OUT_FOLD=$out_fold

mkdir -p $in_fold


gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name/$name 
[ $? -ne 0 ] && echo $msg compile error && exit 1 

/tmp/$name/$name
[ $? -ne 0 ] && echo $msg run error && exit 2 



${IPYTHON:-ipython} --pdb -i $name.py 
[ $? -ne 0 ] && echo $msg ana error && exit 3 

exit 0 


