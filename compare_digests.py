#!/usr/bin/env python3
"""
Compare array digests (SHA256) between two directories with A###/<stem>.npy layouts.

Usage:
    python3 compare_digests.py /path/A /path/B [stems]
    python3 compare_digests.py /path/A /path/B hit,genstep
    python3 compare_digests.py /path/A /path/B    # defaults to "hit,genstep"
"""

import re
import sys
import hashlib
import numpy as np
from pathlib import Path


def digest_npy(path):
    """SHA256 of the raw array bytes (shape + dtype + data)."""
    a = np.load(path, mmap_mode='r')
    return hashlib.sha256(a.tobytes()).hexdigest()[:16]


def main():
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print(f"Usage: {sys.argv[0]} <dir_a> <dir_b> [stems]")
        sys.exit(1)

    dir_a = Path(sys.argv[1])
    dir_b = Path(sys.argv[2])
    stems = sys.argv[3] if len(sys.argv) > 3 else "hit,genstep"
    arrays = [f"{s.strip()}.npy" for s in stems.split(",")]

    print("compare_digests.py")
    print(f"A:        {dir_a}")
    print(f"B:        {dir_b}")
    print(f"stems:    {stems}")
    print(f"patterns: {arrays}")

    pattern = re.compile(r"^A\d+$")
    subdirs_a = sorted(d for d in dir_a.iterdir() if d.is_dir() and pattern.match(d.name))
    subdirs_b = sorted(d for d in dir_b.iterdir() if d.is_dir() and pattern.match(d.name))

    labels_a = {d.name for d in subdirs_a}
    labels_b = {d.name for d in subdirs_b}

    common = sorted(labels_a & labels_b)
    only_a = sorted(labels_a - labels_b)
    only_b = sorted(labels_b - labels_a)

    if only_a:
        print(f"Only in {dir_a}: {only_a}")
    if only_b:
        print(f"Only in {dir_b}: {only_b}")
    mismatches = []
    rows = []

    for label in common:
        for arr in arrays:
            fa = dir_a / label / arr
            fb = dir_b / label / arr
            da = digest_npy(fa)
            db = digest_npy(fb)
            ok = da == db
            if not ok:
                mismatches.append((label, arr))
            # relative paths (just the tag/array part)
            rel = f"{label}/{arr}"
            rows.append((rel, da, db, "OK" if ok else "MISMATCH"))

    # ---- table ----
    rw = max(len(r[0]) for r in rows)  # rel path width
    dw = len(rows[0][1])               # digest width (all same length)
    sw = 8                             # status width

    print()
    print(f"{'file':<{rw}}  {'digest_A':>{dw}}  {'digest_B':>{dw}}  {'status':>{sw}}")
    print("-" * (rw + 2 + dw + 2 + dw + 2 + sw))

    for rel, da, db, status in rows:
        flag = " !" if status != "OK" else ""
        print(f"{rel:<{rw}}  {da:>{dw}}  {db:>{dw}}  {status:>{sw}}{flag}")

    print("-" * (rw + 2 + dw + 2 + dw + 2 + sw))
    print(f"\nCompared {len(common)} dirs × {len(arrays)} arrays = {len(common)*len(arrays)} files")
    print(f"Only in A: {len(only_a)} dirs")
    print(f"Only in B: {len(only_b)} dirs")

    if mismatches:
        print(f"\nMISMATCHES ({len(mismatches)}):")
        for label, arr in mismatches:
            print(f"  {label}/{arr}")
    else:
        print("\nAll digests match.")


if __name__ == "__main__":
    main()
