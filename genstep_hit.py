#!/usr/bin/env python3
"""
Discover A### directories under ALL0_no_opticks_event_name,
load hit.npy / genstep.npy shapes, and populate a (N,2) count array.
"""

import re
import numpy as np
from pathlib import Path

cwd = Path.cwd()
base = cwd / "ALL0_no_opticks_event_name"

# ---- discover directories matching A followed by digits ----
pattern = re.compile(r"^A\d+$")
dirs = sorted(d for d in base.iterdir() if d.is_dir() and pattern.match(d.name))

if not dirs:
    print("No A### directories found.")
    exit()

labels = [d.name for d in dirs]

# ---- load shapes (mmap => metadata only, no data read) ----
counts = np.empty((len(dirs), 2), dtype=np.int32)

for i, d in enumerate(dirs):
    counts[i, 0] = np.load(d / "hit.npy",     mmap_mode='r').shape[0]
    counts[i, 1] = np.load(d / "genstep.npy", mmap_mode='r').shape[0]

# ---- report ----
print(f"\n{'dir':>6s}  {'hit':>10s}  {'genstep':>10s}")
print("-" * 31)
for i, label in enumerate(labels):
    print(f"{label:>6s}  {counts[i,0]:>10,d}  {counts[i,1]:>10,d}")

print("-" * 31)
print(f"{'TOTAL':>6s}  {counts[:,0].sum():>10,d}  {counts[:,1].sum():>10,d}")
print(f"\nRatio genstep/hit: {counts[:,1].sum() / counts[:,0].sum():.3f}")
print(f"Shape of counts array: {counts.shape}")


np.save("genstep_hit.npy", counts)


