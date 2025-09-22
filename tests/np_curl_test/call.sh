#!/usr/bin/env bash

usage(){ cat << EOU

~/np/tests/np_curl_test/call.sh




curl options
-------------

--disable
    dont read ~/.curlrc

-s, --silent
    no progress meter

-v, --verbose
    show request and response info

--fail-with-body
    when the server gives an error, instead of returning document
    describing an error propagate the error to the client as
    well as saving the response


EOU
}

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
DIR=$TMP/tests/np_curl_test


export FOLD=/data1/blyth/tmp/SEvt__createInputGenstep_configuredTest



mkdir -p $DIR
cd $DIR
pwd




#cat ~/.curlrc


#if [ ! -f "arr" ]; then
#   ${IPYTHON:-ipython} -c "import numpy as np ; a = np.ones([512,512,3], dtype=np.uint8) ; open('arr','wb').write(a.tobytes())"
#   [ $? -ne 0 ] && echo $BASH_SOURCE - failed to write raw array data to arr && exit 1
#fi


# -X POST \   ## not needed when have -F ?

curl \
    --disable \
    -s \
    -v \
    --fail-with-body \
    -H "Content-Type: multipart/form-data" \
    -H "x-opticks-token: secret" \
    -H "x-opticks-dtype: float32" \
    -H "x-opticks-shape: (1,6,4)" \
    -H "x-opticks-level: 1" \
    -H "x-opticks-index: 0" \
    -F "upload=@$FOLD/gs.npy" \
    --output $FOLD/ht.npy \
    "http://127.0.0.1:8000/simulate"

[ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl && exit 2

ls -alst .

exit 0

