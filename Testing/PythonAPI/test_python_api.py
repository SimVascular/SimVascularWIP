#!/usr/bin/env python3
"""Smoke test: verifies the SimVascular `sv` Python extension module imports
and exposes its expected submodules. Run via test_python_api.sh so
LD_LIBRARY_PATH is set correctly.
"""
import sys

if len(sys.argv) != 2:
    sys.exit(f"usage: {sys.argv[0]} <path-to-site-packages>")

sys.path.insert(0, sys.argv[1])

import sv

expected_submodules = [
    "geometry",
    "imaging",
    "mesh_utils",
    "meshing",
    "modeling",
    "pathplanning",
    "segmentation",
    "simulation",
    "vmtk",
]

missing = [m for m in expected_submodules if not hasattr(sv, m)]

print(f"Imported sv from: {sv.__file__}")
print(f"Available submodules: {sorted(m for m in dir(sv) if not m.startswith('_'))}")

if missing:
    sys.exit(f"FAIL: missing expected submodules: {missing}")

print("PASS: sv Python API imported successfully with all expected submodules present.")
