#!/usr/bin/env bash

usage(){ cat << EOU

~/np/tests/np_curl_test/call.sh

EOU
}


DIR=/Users/blyth/Downloads
cd $DIR

curl \
    -s \
    -i /dev/stdout \
    -X POST http://127.0.0.1:8000/array_transform  \
    -H "Content-Type: multipart/form-data" \
    -H "x-numpy-token: secret" \
    -H "x-numpy-dtype: uint8" \
    -H "x-numpy-shape: (512,512,3)" \
    -H "x-numpy-level: 1" \
    -F "upload=@arr;type=application/octet-stream" \
    --output out

ls -alst arr out
diff -b arr out

