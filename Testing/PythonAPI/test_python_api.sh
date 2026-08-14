#!/usr/bin/env bash
# Demonstrates that the SimVascular Python API (the `sv` package) is importable.
#
# Usage:
#   test_python_api.sh [SIMWIP_ROOT] [BUILD_DIR]
#
#   SIMWIP_ROOT  Directory containing the SuperBuild dependency install trees
#                (OpenCASCADE-install, VTK-install, ITK-install, GDCM-install,
#                HDF5-install, MMG-install, tinyxml2-install, VMTK-install,
#                and on Windows FreeType-install).
#                Defaults to $SIMWIP_ROOT env var, or ../../simwip relative to
#                this repo checkout.
#   BUILD_DIR    The SimVascular-build directory containing the built `sv`
#                Python package.
#                Defaults to $SIMWIP_ROOT/SuperBuild/SimVascular-build.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

SIMWIP_ROOT="${1:-${SIMWIP_ROOT:-${REPO_ROOT}/../simwip}}"
# Normalize to this shell's native path form (e.g. under MSYS/Git-Bash on
# Windows, a "D:/..."-style argument won't be translated when later used to
# build PATH for a native child process, but "/d/..." will).
SIMWIP_ROOT="$(cd "${SIMWIP_ROOT}" && pwd)"
BUILD_DIR="${2:-${SIMWIP_ROOT}/SuperBuild/SimVascular-build}"
BUILD_DIR="$(cd "${BUILD_DIR}" && pwd)"

# Layout differs by platform: on Unix, Python installs the package under
# lib/pythonX.Y/site-packages; CMake's Windows FindPython puts it under
# Lib/site-packages directly, with no per-version subdir.
SITE_PACKAGES=""
for candidate in \
    "$(find "${BUILD_DIR}/lib" -maxdepth 1 -type d -name "python3.*" 2>/dev/null | head -1)/site-packages" \
    "${BUILD_DIR}/bin/Lib/site-packages" \
    "${BUILD_DIR}/Lib/site-packages"
do
    if [[ -n "${candidate}" && -d "${candidate}" ]]; then
        SITE_PACKAGES="${candidate}"
        break
    fi
done

if [[ -z "${SITE_PACKAGES}" ]]; then
    echo "Could not find an sv site-packages directory under ${BUILD_DIR}" >&2
    exit 1
fi

# Directories that may contain shared libraries/DLLs the sv extension
# modules depend on at import time. Not all of these exist on every
# platform (e.g. FreeType-install is Windows-only, bin/Release is a
# Visual Studio multi-config artifact) -- only existing ones are used below.
RUNTIME_DIRS=(
    "${SIMWIP_ROOT}/OpenCASCADE-install/lib"
    "${SIMWIP_ROOT}/OpenCASCADE-install/bin"
    "${SIMWIP_ROOT}/VTK-install/lib"
    "${SIMWIP_ROOT}/VTK-install/bin"
    "${SIMWIP_ROOT}/ITK-install/lib"
    "${SIMWIP_ROOT}/ITK-install/bin"
    "${SIMWIP_ROOT}/GDCM-install/lib"
    "${SIMWIP_ROOT}/GDCM-install/bin"
    "${SIMWIP_ROOT}/HDF5-install/lib"
    "${SIMWIP_ROOT}/HDF5-install/bin"
    "${SIMWIP_ROOT}/MMG-install/lib"
    "${SIMWIP_ROOT}/MMG-install/bin"
    "${SIMWIP_ROOT}/tinyxml2-install/lib"
    "${SIMWIP_ROOT}/tinyxml2-install/bin"
    "${SIMWIP_ROOT}/VMTK-install/lib"
    "${SIMWIP_ROOT}/VMTK-install/bin"
    "${SIMWIP_ROOT}/FreeType-install/bin"
    "${BUILD_DIR}/lib"
    "${BUILD_DIR}/bin"
    "${BUILD_DIR}/bin/Release"
)

# Windows resolves DLL dependencies via PATH; there's no equivalent of
# LD_LIBRARY_PATH (Linux) / DYLD_LIBRARY_PATH (macOS).
case "$(uname -s)" in
    MINGW*|MSYS*|CYGWIN*)
        for dir in "${RUNTIME_DIRS[@]}"; do
            [[ -d "${dir}" ]] && PATH="${dir}:${PATH}"
        done
        export PATH
        ;;
    Darwin)
        for dir in "${RUNTIME_DIRS[@]}"; do
            [[ -d "${dir}" ]] && DYLD_LIBRARY_PATH="${dir}${DYLD_LIBRARY_PATH:+:${DYLD_LIBRARY_PATH}}"
        done
        export DYLD_LIBRARY_PATH
        ;;
    *)
        for dir in "${RUNTIME_DIRS[@]}"; do
            [[ -d "${dir}" ]] && LD_LIBRARY_PATH="${dir}${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"
        done
        export LD_LIBRARY_PATH
        ;;
esac

# On Windows, `python3` on PATH is often a non-functional stub (the "App
# execution alias" shim Windows installs even when a real Python lives
# elsewhere) that exits nonzero instead of running, so each candidate is
# actually exercised rather than just checked for existence.
PYTHON_BIN=""
for candidate in python3 python; do
    if command -v "${candidate}" >/dev/null 2>&1 && "${candidate}" -c "" >/dev/null 2>&1; then
        PYTHON_BIN="${candidate}"
        break
    fi
done
if [[ -z "${PYTHON_BIN}" ]]; then
    echo "Could not find a working python3 or python interpreter on PATH" >&2
    exit 1
fi

exec "${PYTHON_BIN}" "${SCRIPT_DIR}/test_python_api.py" "${SITE_PACKAGES}"
