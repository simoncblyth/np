#!/usr/bin/env python3
"""
Scan current directory recursively for .npy files and report their shapes.
Uses mmap_mode='r' so arrays are not loaded into memory.
"""

import numpy as np
from pathlib import Path

cwd = Path.cwd()
npy_paths = sorted(cwd.rglob("*.npy"))

if not npy_paths:
    print("No .npy files found.")
    exit()

# Determine max path length for column alignment
max_path_len = max(len(str(p)) for p in npy_paths)

print(f"\n{'path':<{max_path_len}}  {'shape':>20s}  dtype")
print("-" * max_path_len + "  " + "-" * 20 + "  " + "-" * 10)

for p in npy_paths:
    #print(p)
    if "sfr" in p.name: continue

    a = np.load(p, mmap_mode='r')
    rel = str(p) if not p.is_relative_to(cwd) else str(p.relative_to(cwd))
    print(f"{rel:<{max_path_len}}  {str(a.shape):>20s}  {str(a.dtype):>10s}")

print(f"\nTotal: {len(npy_paths)} .npy files\n")
