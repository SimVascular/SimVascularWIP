# macOS arm64 Build Report

This report documents the local changes made to build SimVascularWIP from
source on one macOS arm64 system. The goal is to make the build issues and
patches reviewable so maintainers can decide which changes are general fixes
and which are local/toolchain-specific workarounds.

## System Information

Observed system and toolchain:

- Host OS: macOS 26.6, build 25G72
- Kernel: Darwin 25.6.0, arm64
- Compiler: Apple clang 21.0.0, target `arm64-apple-darwin25.6.0`
- CMake: 4.3.4
- Homebrew prefix: `/opt/homebrew`
- Qt: 6.11.1 from `/opt/homebrew/opt/qt`
- Python: 3.12.4 from `/opt/homebrew/opt/python@3.12`
- Build type: Release

Paths below are written relative to `$SIMWIP_ROOT`, the superbuild directory
holding the dependency install trees (`../simwip` alongside the repo checkout,
per the README):

- SimVascular build directory: `$SIMWIP_ROOT/SuperBuild/SimVascular-build`
- Dependency install trees:
  - VTK: `$SIMWIP_ROOT/VTK-install/lib/cmake/vtk-9.3`
  - ITK: `$SIMWIP_ROOT/ITK-install/lib/cmake/ITK-5.4`
  - OpenCASCADE: `$SIMWIP_ROOT/OpenCASCADE-install/lib/cmake/opencascade`
  - VMTK: `$SIMWIP_ROOT/VMTK-install/lib`
  - MMG: `$SIMWIP_ROOT/MMG-install/lib/cmake/mmg`

The final iteration was done by rebuilding the inner SimVascular CMake project
directly after the dependency superbuild had completed.

## Environment Issue Not Patched

An early configure attempt mixed Qt package files from two installations:

- Homebrew Qt under `/opt/homebrew`
- Conda Qt under a separate `miniforge3` environment

The failure included:

```text
Unknown CMake command "_qt_internal_should_include_targets"
```

This was treated as a local configuration/cache issue, not a source patch. A
clean build directory and a consistent `Qt6_DIR`, for example
`/opt/homebrew/opt/qt/lib/cmake/Qt6`, avoided this class of error.

## Source Changes

### `CMakeLists.txt`

Changed Python discovery from a minimum-only version request to an explicit
Python 3.12 range:

- `find_package(Python 3.12...<3.13 COMPONENTS Interpreter Development.Module REQUIRED)`
- `find_package(Python3 3.12...<3.13 COMPONENTS Interpreter Development REQUIRED)`

Reason:

The build needed to stay on Homebrew Python 3.12. Without the explicit version
range and interpreter component, CMake could select another Python installation
or version while later generated headers and extension targets expected the
Python version used during configuration.

### `SuperBuild/CMakeLists.txt`

Added:

- `-DCMAKE_POLICY_VERSION_MINIMUM:STRING=3.5`
- forwarding of `Python3_EXECUTABLE` and `Python3_ROOT_DIR` to the inner
  SimVascular configure step

Reason:

CMake 4 rejected older dependency projects whose minimum policy versions are
below current CMake expectations. Setting `CMAKE_POLICY_VERSION_MINIMUM=3.5`
allowed those older dependency CMake projects to configure under CMake 4.

The Python forwarding kept the inner SimVascular build aligned with the Python
3.12 interpreter selected at the top level.

### `SuperBuild/External_VTK.cmake`

Added a `PATCH_COMMAND` that runs `SuperBuild/PatchVTKMacOS.cmake` against the
downloaded VTK source tree.

Also forwarded:

- `Python3_EXECUTABLE`
- `Python3_ROOT_DIR`

Reason:

VTK needed source patches for this macOS/AppleClang build, and VTK's Python
configuration needed to use the same Python 3.12 interpreter/root selected for
the rest of the build.

### `SuperBuild/PatchVTKMacOS.cmake`

New patch script for the downloaded VTK source tree.

It applies three idempotent edits:

1. Patches VTK's vendored zlib header:
   `ThirdParty/zlib/vtkzlib/zutil.h`

   Error addressed:

   ```text
   fdopen macro redefinition
   ```

   Reason:

   The old zlib macOS preprocessor check matched modern Apple platforms and
   attempted to redefine `fdopen`.

2. Patches VTK's vendored libpng header:
   `ThirdParty/png/vtkpng/pngpriv.h`

   Error addressed:

   ```text
   fatal error: 'fp.h' file not found
   ```

   Reason:

   A legacy classic Mac conditional was triggered on modern macOS because
   `TARGET_OS_MAC` was defined. The patch excludes `__APPLE__` from that
   legacy branch.

3. Patches VTK's octree implementation:
   `Utilities/octree/octree/octree_node.txx`

   Error addressed:

   ```text
   no member named '_M_chilren'
   ```

   Reason:

   The source referenced `_M_chilren`, which appears to be a typo for
   `m_children`.

### `SuperBuild/External_OpenCASCADE.cmake`

Added a `PATCH_COMMAND` that runs
`SuperBuild/PatchOpenCASCADEMacOS.cmake` against the downloaded OpenCASCADE
source tree.

Reason:

OpenCASCADE needed a small source compatibility patch for the C++ type checking
used by this AppleClang/libc++ toolchain.

### `SuperBuild/PatchOpenCASCADEMacOS.cmake`

New patch script for the downloaded OpenCASCADE source tree.

It patches:

`src/StdPrs/StdPrs_BRepFont.cxx`

Error addressed:

```text
cannot initialize a variable of type 'const char *' with an rvalue of type 'unsigned char *'
```

Reason:

The FreeType outline tag buffer is exposed as unsigned byte data, but the code
stores it in a `const char*`. The patch uses:

```cpp
reinterpret_cast<const char*>(&anOutline->tags[aStartIndex])
```

### `Source/Core/vtk.module`

Added VTK module dependencies:

- `VTK::FiltersGeometry`
- `VTK::IOXML`

Error addressed:

```text
Undefined symbols for architecture arm64:
  vtkXMLWriter::SetInputData(vtkDataObject*)
  vtkXMLWriterBase::Write()
  vtkXMLPolyDataWriter::New()
  vtkXMLUnstructuredGridWriter::New()
  vtkDataSetSurfaceFilter::New()
```

Reason:

`SVCore` uses XML VTK writers and `vtkDataSetSurfaceFilter` in
`Source/Core/sv_vtk_utils.cxx`, but its VTK module metadata did not declare
the modules that provide those symbols.

### `Source/sv1/Mesh/_AdaptObject/vtk.module`

Added VTK module dependencies:

- `VTK::CommonDataModel`
- `VTK::FiltersGeneral`
- `VTK::FiltersGeometry`
- `VTK::IOXML`

Error addressed:

```text
Undefined symbols for architecture arm64:
  vtkGradientFilter::New()
```

Reason:

`Source/sv1/Mesh/_AdaptObject/sv_adapt_utils.cxx` uses
`vtkGradientFilter`, `vtkDataSetSurfaceFilter`, and
`vtkXMLUnstructuredGridWriter`, but the module metadata only listed
`VTK::CommonCore`, `VTK::SVCore`, and `VTK::SV1MeshMeshObject`.

### `Source/sv1/Geometry/sv_ggems.cxx`

Added:

```cpp
#include <algorithm>
```

Changed the `acos` input clamp from:

```cpp
std::max(-1.0, ((1.0) < (s) ? (1.0) : (s)))
```

to:

```cpp
std::max(-1.0, std::min(1.0, s))
```

Error addressed:

```text
error: no member named 'max' in namespace 'std'; did you mean 'fmax'?
error: static assertion failed ...
```

Reason:

The file used `std::max` without including `<algorithm>`. On this libc++
toolchain, including only math headers caused overload resolution to fall into
the math `fmax` path and fail. The new expression keeps the same clamp behavior
while using standard `<algorithm>` functions explicitly.

### `Source/vtkSV/Modules/_Segmentation/CMakeLists.txt`

Added explicit VMTK link libraries:

- `vtkvmtkCommon`
- `vtkvmtkComputationalGeometry`
- `vtkvmtkDifferentialGeometry`
- `vtkvmtkIO`
- `vtkvmtkMisc`
- `vtkvmtkSegmentation`

Error addressed:

```text
Undefined symbols for architecture arm64:
  vtkvmtkMath::AngleBetweenNormals(double*, double*)
  vtkvmtkMergeCenterlines::New()
  vtkvmtkVoronoiDiagram3D::New()
  vtkvmtkCenterlineUtilities::...
  vtkvmtkCenterlineSplittingAndGroupingFilter::...
```

Reason:

`SVSegmentation` includes VMTK headers and uses VMTK classes, but only added
`${VMTK_INCLUDE_DIRS}`. It did not link the VMTK libraries that define those
symbols. The link list mirrors the existing VMTK usage in
`Source/sv1/Mesh/_MeshUtils/CMakeLists.txt`.

### `Source/_PythonAPI/Segmentation_PyModule.cxx`

Removed:

```cpp
#pragma message "TEST:" PYTHON_MAJOR_VERSION
```

Error addressed:

```text
error: pragma message requires parenthesized string
```

Reason:

`PYTHON_MAJOR_VERSION` expands to the numeric token `3`, not a string literal.
The line appeared to be diagnostic/debug output and was removed.

### `Source/_PythonAPI/SimulationROM_PyClass.cxx`

Added:

```cpp
#include <sstream>
```

Error addressed:

```text
error: implicit instantiation of undefined template 'std::basic_istringstream<char>'
```

Reason:

The file uses `std::istringstream` but did not include `<sstream>`.

## Verification Performed

Focused targets were rebuilt after their corresponding fixes:

```bash
BUILD_DIR=$SIMWIP_ROOT/SuperBuild/SimVascular-build
cmake --build "$BUILD_DIR" --target SVCore --parallel 1
cmake --build "$BUILD_DIR" --target SV1MeshAdaptObject --parallel 1
cmake --build "$BUILD_DIR" --target SV1Geometry --parallel 1
cmake --build "$BUILD_DIR" --target SVSegmentation --parallel 1
cmake --build "$BUILD_DIR" --target SVPythonAPI --parallel 1
```

The overall build subsequently completed successfully.

Also checked:

```bash
git diff --check
```

No whitespace errors were reported.

## Likely Classification

Likely general source/build-system fixes:

- Missing VTK dependencies in `Source/Core/vtk.module`
- Missing VTK dependencies in `Source/sv1/Mesh/_AdaptObject/vtk.module`
- Missing VMTK link libraries in `Source/vtkSV/Modules/_Segmentation/CMakeLists.txt`
- Missing `<algorithm>` in `Source/sv1/Geometry/sv_ggems.cxx`
- Missing `<sstream>` in `Source/_PythonAPI/SimulationROM_PyClass.cxx`
- Removing the invalid debug `#pragma message` in
  `Source/_PythonAPI/Segmentation_PyModule.cxx`

Possibly toolchain- or dependency-version-specific fixes:

- `CMAKE_POLICY_VERSION_MINIMUM=3.5` for CMake 4 compatibility in old external
  dependency projects
- VTK vendored zlib/libpng/octree patches
- OpenCASCADE FreeType outline tag cast patch
- Explicit Python 3.12 pinning/forwarding through the superbuild

Likely local setup issue:

- Initial mixed Homebrew/Conda Qt CMake package state

## Post-Build Issue: `import sv` on macOS

Found while running the Python API smoke test
(`Testing/PythonAPI/test_python_api.sh`) against the completed build.

### `Source/_PythonAPI/sv_package_init.py`

This file is copied to `<build>/lib/python3.12/site-packages/sv/__init__.py`
and loads the compiled extension library with `ctypes.PyDLL`. Its
`_find_lib_path()` helper built the library file name with only two cases:

```python
lib_name = ("" if os.name == "nt" else "lib") + "vtkSVPythonAPI" + (".dll" if os.name == "nt" else ".so")
```

So every non-Windows platform looked for `libvtkSVPythonAPI.so`. On macOS the
build produces `libvtkSVPythonAPI.dylib`, so none of the candidate paths
matched, `_find_lib_path()` fell through to its bare-name return, and
`dlopen` failed:

```text
OSError: dlopen(libvtkSVPythonAPI.so, 0x0006): tried: 'libvtkSVPythonAPI.so' (no such file), ...
```

Fix:

Replaced the single computed name with a `_lib_names()` helper returning the
per-platform candidates (`vtkSVPythonAPI.dll` on Windows,
`libvtkSVPythonAPI.dylib` then `libvtkSVPythonAPI.so` on macOS,
`libvtkSVPythonAPI.so` elsewhere), and search each known directory layout for
each candidate name. `.so` is still tried on macOS because some
build/packaging setups force that suffix there.

Classification: likely a general fix, not macOS-local. The old code could not
have worked on any macOS build.

### Related observation, not patched

`Testing/PythonAPI/test_python_api.sh` exports `LD_LIBRARY_PATH`, which the
macOS dynamic loader ignores; the macOS equivalent is `DYLD_LIBRARY_PATH`.
This did not block the test, because the extension's dependency libraries
resolve through the RPATHs recorded in `libvtkSVPythonAPI.dylib`. Left as is.

### Verification

After the patch, the build directory was reconfigured so the updated file was
re-copied into the `sv` package (it is installed with `configure_file(...
COPYONLY)` at configure time, not build time):

```bash
cmake "$SIMWIP_ROOT/SuperBuild/SimVascular-build"
Testing/PythonAPI/test_python_api.sh
```

Result:

```text
Imported sv from: .../lib/python3.12/site-packages/sv/__init__.py
Available submodules: ['ctypes', 'geometry', 'imaging', 'mesh_utils', 'meshing', 'modeling', 'os', 'pathplanning', 'segmentation', 'simulation', 'sys', 'vmtk']
PASS: sv Python API imported successfully with all expected submodules present.
```

No `.so` symlink or other workaround is present in the build tree; the test
passes against `libvtkSVPythonAPI.dylib` directly.

