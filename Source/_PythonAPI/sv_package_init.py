"""sv - SimVascular Python API package.

The sv.geometry / sv.modeling / sv.segmentation / sv.meshing / sv.simulation /
sv.pathplanning / sv.imaging / sv.vmtk / sv.mesh_utils submodules are plain
CPython extension modules, all compiled into the "SVPythonAPI" C++ library
(libvtkSVPythonAPI.so -- NOT the same file as sv/vtkSVPythonAPI.so, which is
a separate, VTK-generated shared object that only wraps VTK-style C++
classes and has none of these). Their init functions are deliberately named
things like PyInit_PyGeometry rather than PyInit_geometry, so that an
*embedding* application controls what name each one is registered under, via

    PyImport_AppendInittab("geometry", PyInit_PyGeometry)

called before Py_Initialize(). See Source/_Application/SimVascular_Init_py.cxx
for the reference list this mirrors.

That mechanism only works for an application that creates its own
interpreter. It can't be used by code loaded into an *already-running*
interpreter -- e.g. 3D Slicer's -- since PyImport_AppendInittab must run
before Py_Initialize(). This file works around that: it loads the compiled
extension directly with ctypes, calls each named init function by hand (which
is all PyImport_AppendInittab-based loading does under the hood for a
single-phase-init module like these), and registers the result in
sys.modules under the desired dotted name. That works in any CPython
interpreter, embedded or not, and doesn't depend on which VTK build
libvtkSVPythonAPI happens to be linked against.
"""

import ctypes
import os
import sys

# (python module name, C PyInit_* function name in libvtkSVPythonAPI)
# Keep this in sync with Source/_Application/SimVascular_Init_py.cxx's
# SimVascular_pyInit().
_SV_PYTHON_API_MODULES = [
    ("segmentation", "PyInit_PySegmentation"),
    ("geometry", "PyInit_PyGeometry"),
    ("imaging", "PyInit_PyImaging"),
    ("pathplanning", "PyInit_PyPathplanning"),
    ("modeling", "PyInit_PyModeling"),
    ("simulation", "PyInit_PySimulation"),
    ("vmtk", "PyInit_PyVmtk"),
    ("meshing", "PyInit_PyMeshing"),
    ("mesh_utils", "PyInit_PyMeshUtils"),
]


def _lib_names():
    # Shared-library naming differs per platform: libvtkSVPythonAPI.so on
    # Linux, libvtkSVPythonAPI.dylib on macOS, vtkSVPythonAPI.dll on Windows.
    if os.name == "nt":
        return ("vtkSVPythonAPI.dll",)
    if sys.platform == "darwin":
        # .so is also tried on macOS since some build/packaging setups force
        # that suffix even there.
        return ("libvtkSVPythonAPI.dylib", "libvtkSVPythonAPI.so")
    return ("libvtkSVPythonAPI.so",)


def _find_lib_path():
    lib_names = _lib_names()
    here = os.path.dirname(os.path.abspath(__file__))

    # Candidate locations relative to this file, covering the layouts we
    # know about. This file currently lives at
    # <build-or-install-prefix>/lib/pythonX.Y/site-packages/sv/__init__.py,
    # with the library three directories up, in .../lib/. A Slicer
    # extension will likely place things differently once this actually
    # gets built against Slicer's VTK -- add that layout here once known.
    for directory in (
        os.path.join(here, "..", "..", ".."),  # .../lib/<name> (current layout)
        os.path.join(here, ".."),  # a flatter, single-directory layout
        here,  # right next to this file
    ):
        for lib_name in lib_names:
            candidate = os.path.normpath(os.path.join(directory, lib_name))
            if os.path.exists(candidate):
                return candidate

    # Fall back to letting the OS loader search its normal paths (RPATH,
    # LD_LIBRARY_PATH/DYLD_LIBRARY_PATH/PATH, ldconfig cache, etc). Works if
    # whatever packages this for its target environment (e.g. a Slicer
    # extension) sets one of those up, which is the standard way to make a
    # bundled shared library findable.
    return lib_names[0]


_LIB_PATH = _find_lib_path()


def _load_extension_modules():
    # ctypes/dlopen report their own errors if _LIB_PATH can't be found or
    # loaded (e.g. missing dependency libraries); let that propagate instead
    # of masking it, since a partially-working sv package is more confusing
    # than a clear load error.
    #
    # PyDLL (not CDLL) keeps the GIL held across the call, which these need
    # since they call straight back into the Python C API.
    lib = ctypes.PyDLL(_LIB_PATH)

    for name, init_func_name in _SV_PYTHON_API_MODULES:
        init_func = getattr(lib, init_func_name, None)
        if init_func is None:
            # Built without this module (e.g. VMTK/TetGen/MMG support
            # disabled at compile time) -- skip it.
            continue

        init_func.restype = ctypes.py_object
        try:
            module = init_func()
        except Exception as exception:
            sys.stderr.write(f"sv: failed to initialize 'sv.{name}': {exception}\n")
            continue

        module.__name__ = "sv." + name
        module.__package__ = "sv"
        sys.modules["sv." + name] = module
        globals()[name] = module


_load_extension_modules()
del (
    _load_extension_modules,
    _find_lib_path,
    _lib_names,
    _LIB_PATH,
    _SV_PYTHON_API_MODULES,
)
