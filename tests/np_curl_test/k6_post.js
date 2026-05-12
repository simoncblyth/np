
/**



Gemini translation of curl commandline::

    index=99
    count=1000000
    level=0
    token=secret
    meta=via-curl-cli
    htname=$(printf  "ht%0.3d_cli.npy" $index)

    curl \
        --disable \
        -s \
        -v \
        --fail-with-body \
        -H "x-opticks-token: $token" \
        -H "x-opticks-level: $level" \
        -H "x-opticks-index: $index" \
        -H "x-opticks-count: $count" \
        -H "x-opticks-meta: $meta" \
        -F "upload=@$FOLD/gs.npy" \
        --output $FOLD/$htname \
        "$NP_CURL_API_URL"



**/


import http from 'k6/http';
import { check, fail } from 'k6';

// 1. Load the file into memory (equivalent to @$FOLD/gs.npy)
// Replace 'path/to/gs.npy' with your actual file path

const foldDir = __ENV.FOLD || './data';
const binFile = open(`${foldDir}/gs.npy`, 'b');

export const options = {
  vus: 1, // Number of virtual users
  duration: '10s', // Duration of the test
};

export default function () {
  const count = 1000000;
  const level = 0;
  const token = 'secret';
  const meta = 'via-k6-script';

  // k6 automatically handles the Boundary for multipart/form-data
  const url = __ENV.NP_CURL_API_URL || 'http://localhost:8080/upload';
  const index = (__VU * 10000) + __ITER;

  const data = {
    upload: http.file(binFile, 'gs.npy'),
  };

  const params = {
    headers: {
      'x-opticks-token': token,
      'x-opticks-level': String(level),
      'x-opticks-index': String(index),
      'x-opticks-count': String(count),
      'x-opticks-meta': meta,
    },
  };

  const res = http.post(url, data, params);

  // Equivalent to --fail-with-body
  check(res, {
    'status is 200': (r) => r.status === 200,
  }) || fail(`Request failed with status ${res.status}`);

  // Note: k6 does not typically save response bodies to disk (like --output)
  // to avoid disk I/O bottlenecks during load tests.
}

