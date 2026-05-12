/**
k6_load.js
===========

k6 VUS Virtual Users are equivalent of threads, one
being stuck does not hold up the others.

   -u 10


k6 run -u 50 -d 1m k6_load.js
    Runs 50 parallel VUs for 1 minute.

k6 run --vus 10 --iterations 100 k6_load.js
    Runs exactly 100 requests total, distributed across 10 VUs



**/


import http from 'k6/http';
import { check, sleep } from 'k6';
import { Counter } from 'k6/metrics';

// Create a custom counter
const rateLimitCounter = new Counter('rate_limited_requests');

// 1. Setup the directory from environment variable
// Default to './data' if FOLD is not provided
const foldDir = __ENV.FOLD || './data';
const outfoldDir = __ENV.K6FOLD || '/tmp';


// 1. Read the file content
const smallMeta = open(`${foldDir}/small_meta.txt`);
const mediumMeta = open(`${foldDir}/medium_meta.txt`);
const largeMeta = open(`${foldDir}/large_meta.txt`);

function getMetaValue(content, key) {
  // Uses a regex to find the key followed by a colon and the value
  const match = content.match(new RegExp(`${key}:\\s*(.+)`));
  return match ? match[1].trim() : null;
}

// 3. Extract num_ph
const smallCount = getMetaValue(smallMeta, 'num_ph');
const mediumCount = getMetaValue(mediumMeta, 'num_ph');
const largeCount = getMetaValue(largeMeta, 'num_ph');

// 2. Preload files (Init Stage)
const fileMap = {
  small:  { bin: open(`${foldDir}/small.npy`, 'b'), count: smallCount,   name: 'small.npy' },
  medium: { bin: open(`${foldDir}/medium.npy`, 'b'), count: mediumCount,  name: 'medium.npy' },
  large:  { bin: open(`${foldDir}/large.npy`, 'b'), count: largeCount, name: 'large.npy' },
};

export const options = {
  vus: 5,
  duration: '30s',
};

export default function () {
  // 3. Pick a file size (Weighted Distribution)
  const rng = Math.random();
  let size;
  if (rng < 0.7) size = 'small';
  else if (rng < 0.9) size = 'medium';
  else size = 'large';

  const selectedFile = fileMap[size];

  // 4. Dynamic Bookkeeping: Use __ITER and __VU for unique indices
  // __ITER is the unique iteration number for the current VU
  // index will be unique across the whole test run
  const uniqueIndex = (__VU * 10000) + __ITER;

  const url = __ENV.NP_CURL_API_URL;

  const data = {
    upload: http.file(selectedFile.bin, selectedFile.name),
  };

  const params = {
    headers: {
      'x-opticks-token': 'secret',
      'x-opticks-level': '0',
      'x-opticks-index': String(uniqueIndex),
      'x-opticks-count': String(selectedFile.count), // Controls the "lane"
      'x-opticks-meta': `k6-upload-${size}`,
    },
  };

  const res = http.post(url, data, params);

  const isRateLimited = res.status === 429;

  if (isRateLimited) {

    rateLimitCounter.add(1);

    const waitTime = parseInt(res.headers['Retry-After']) || 1; // Fallback to 1s
    console.warn(`Server requested retry after: ${waitTime}s`);
    sleep(waitTime);
    res = http.post(url, data, params);
  }


  check(res, {
    'status is 200': (r) => r.status === 200,
    'handled gracefully (200 or 429)': (r) => [200, 429].includes(r.status),
  });



  sleep(0.5);
}




export function handleSummary(data) {
  const rateLimitCount = data.metrics.rate_limited_requests ? data.metrics.rate_limited_requests.values.count : 0;
  const totalRequests = data.metrics.http_reqs.values.count;
  const failureRate = ((rateLimitCount / totalRequests) * 100).toFixed(2);

  console.log(`

  smallCount  : ${smallCount}
  mediumCount : ${mediumCount}
  largeCount  : ${largeCount}

  ==============================================================
  VRAM LOAD TEST REPORT
  Total Requests: ${totalRequests}
  429 Rate Limited: ${rateLimitCount} (${failureRate}%)
  ==============================================================
  `);

  return {
    'stdout': JSON.stringify(data), // Still print the standard summary
    [`${outfoldDir}/summary.json`]: JSON.stringify(data), // Save full raw data to a file
  };
}











