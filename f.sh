#!/bin/bash -l 
usage(){ cat << EOU
~/np/f.sh 
===========

Usage example::

    GEOM std   # an opticks bash function for changing directories
    ~/np/f.sh  # open invoking directory as an np.fold:Fold with ipython

For easy access use bash function::

    f(){ ~/np/f.sh ; : ~/.bash_profile ;  }

EOU
}
DIR=$(cd $(dirname $BASH_SOURCE) && pwd)
#${IPYTHON:-ipython} --pdb -i $DIR/f.py 
${IPYTHON:-ipython} --pdb -i $DIR/fold.py 

