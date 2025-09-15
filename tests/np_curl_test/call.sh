#!/usr/bin/env bash

usage(){ cat << EOU

~/np/tests/np_curl_test/call.sh


HMM getting error from commandline curl, but the
service gives HTTP 200 which means OK::

   curl: (3) URL using bad/illegal format or missing URL

THIS MAY BE RELATED TO THE CURL VERSION AS FIND
FROM C++ np_curl_test.sh THAT MUST USE NEWER CURL
THAN SYSTEM ON A

EOU
}

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
DIR=$TMP/tests/np_curl_test

mkdir -p $DIR
cd $DIR
pwd

cat ~/.curlrc

if [ ! -f "arr" ]; then
   ${IPYTHON:-ipython} -c "import numpy as np ; a = np.ones([512,512,3], dtype=np.uint8) ; open('arr','wb').write(a.tobytes())"
   [ $? -ne 0 ] && echo $BASH_SOURCE - failed to write raw array data to arr && exit 1
fi

#    -s \
# type=application/octet-stream" \
curl \
    -i /dev/stdout \
    --fail-with-body \
    -X POST "http://127.0.0.1:8000/array_transform" \
    -H "Content-Type: multipart/form-data" \
    -H "x-numpy-token: secret" \
    -H "x-numpy-dtype: uint8" \
    -H "x-numpy-shape: (512,512,3)" \
    -H "x-numpy-level: 1" \
    -F "upload=@$DIR/arr" \
    --output $DIR/out

[ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl && exit 2

ls -alst .

exit 0

