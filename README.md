# SimVascularWIP

## Requirements

- CMake 3.26+
- A C/C++17 compiler
- Git
- Python 3.12 (with development headers)
- Qt6 6.10+ (Core, CoreTools, Gui, Widgets, Xml) — not built by the superbuild, must be pre-installed

Everything else (VTK, GDCM, HDF5, ITK, OpenCASCADE, MMG, TetGen, tinyxml2,
VMTK) is fetched and built from source by the CMake superbuild. See
`Dependencies.md` for version pins and per-dependency notes.

## Building

The superbuild is enabled by default (`SimVascular_SUPERBUILD=ON`) and drives
the whole process — configuring and building it builds every dependency
followed by SimVascular itself.

```bash
mkdir -p ../simwip && cd ../simwip

cmake ../SimVascularWIP \
  -DQt6_DIR=/path/to/Qt/6.10.x/gcc_64/lib/cmake/Qt6

make -j$(nproc)
```

Useful CMake options (pass as `-D<OPTION>=<VALUE>`):

| Option | Default | Purpose |
|---|---|---|
| `SimVascular_SUPERBUILD` | `ON` | Build dependencies via superbuild. Set `OFF` only if all deps are already installed and their `*_DIR` variables are supplied. |
| `SV_WRAP_PYTHON` | `ON` | Build the `sv` Python extension module. |
| `BUILD_SHARED_LIBS` | `ON` | Build shared vs. static libraries. |
| `CMAKE_BUILD_TYPE` | `Release` | Standard CMake build type. |

The superbuild produces one install tree per dependency (e.g.
`VTK-install/`, `OpenCASCADE-install/`) alongside a
`SuperBuild/SimVascular-build/` directory containing the actual SimVascular
build (libraries under `lib/`, the Python package under
`lib/python3.12/site-packages/sv/`).

If you only need to iterate on SimVascular itself after the dependencies are
already built, reconfigure/rebuild directly in
`SuperBuild/SimVascular-build/` instead of re-running the top-level build —
it's a normal (non-superbuild) CMake project pointed at the dependency
install trees via cached `*_DIR` variables.

## Testing

### Python API smoke test

Verifies that the `sv` Python extension module built above is importable and
exposes its expected submodules (`geometry`, `imaging`, `meshing`,
`modeling`, `pathplanning`, `segmentation`, `simulation`, `vmtk`, ...).

```bash
Testing/PythonAPI/test_python_api.sh
```

By default it assumes the superbuild install trees live in `../simwip`
relative to this repo checkout and the build lives in
`../simwip/SuperBuild/SimVascular-build`. Override either with positional
arguments if your layout differs:

```bash
Testing/PythonAPI/test_python_api.sh <SIMWIP_ROOT> [BUILD_DIR]
```

## Linting

The `Lint` GitHub Actions workflow (`.github/workflows/lint.yml`) checks
pull requests with `clang-format` (C++, via `.clang-format`) and `ruff`
(Python, via `ruff.toml`). Both only look at lines/files a PR actually
changes — most of `Source/sv1` and `Source/sv4gui` predates this fork and
doesn't conform, so the whole tree isn't linted, only new/changed code.

To check or fix formatting locally before pushing:

```bash
# C++ — only the lines changed since a given base ref/commit
git-clang-format <base-ref>

# Python
ruff check <changed files>
ruff format <changed files>
```
