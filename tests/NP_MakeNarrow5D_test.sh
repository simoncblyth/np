#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_MakeNarrow5D_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

TEST=NP_MakeNarrow5D_test ./NP_MakeNarrow_test.sh $*

