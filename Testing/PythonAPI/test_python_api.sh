#!/usr/bin/env bash
# Demonstrates that the SimVascular Python API (the `sv` package) is importable.
#
# Usage:
#   test_python_api.sh [SIMWIP_ROOT] [BUILD_DIR]
#
#   SIMWIP_ROOT  Directory containing the SuperBuild dependency install trees
#                (OpenCASCADE-install, VTK-install, ITK-install, GDCM-install,
#                HDF5-install, MMG-install, tinyxml2-install, VMTK-install).
#                Defaults to $SIMWIP_ROOT env var, or ../../simwip relative to
#                this repo checkout.
#   BUILD_DIR    The SimVascular-build directory containing the built `sv`
#                Python package under lib/python3.*/site-packages.
#                Defaults to $SIMWIP_ROOT/SuperBuild/SimVascular-build.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

SIMWIP_ROOT="${1:-${SIMWIP_ROOT:-$(cd "${REPO_ROOT}/../simwip" && pwd)}}"
BUILD_DIR="${2:-${SIMWIP_ROOT}/SuperBuild/SimVascular-build}"

SITE_PACKAGES="$(find "${BUILD_DIR}/lib" -maxdepth 1 -type d -name "python3.*" | head -1)/site-packages"

if [[ ! -d "${SITE_PACKAGES}" ]]; then
    echo "Could not find site-packages under ${BUILD_DIR}/lib" >&2
    exit 1
fi

# Runtime libraries needed to resolve the extension module's shared-lib deps.
export LD_LIBRARY_PATH="\
${SIMWIP_ROOT}/OpenCASCADE-install/lib:\
${SIMWIP_ROOT}/VTK-install/lib:\
${SIMWIP_ROOT}/ITK-install/lib:\
${SIMWIP_ROOT}/GDCM-install/lib:\
${SIMWIP_ROOT}/HDF5-install/lib:\
${SIMWIP_ROOT}/MMG-install/lib:\
${SIMWIP_ROOT}/tinyxml2-install/lib:\
${SIMWIP_ROOT}/VMTK-install/lib:\
${BUILD_DIR}/lib\
${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"

exec python3 "${SCRIPT_DIR}/test_python_api.py" "${SITE_PACKAGES}"
