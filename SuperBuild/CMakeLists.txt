cmake_minimum_required(VERSION 3.26..3.26)

find_package(Git REQUIRED)
include(ExternalProject)

#-----------------------------------------------------------------------------
# Common CMake arguments forwarded to all external projects
#-----------------------------------------------------------------------------
set(ep_common_cmake_args
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
  -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
  -DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
  -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON
  -DCMAKE_CXX_EXTENSIONS:BOOL=OFF
  -DCMAKE_POLICY_VERSION_MINIMUM:STRING=3.5
  -DBUILD_TESTING:BOOL=OFF
)

#-----------------------------------------------------------------------------
# External dependencies
#-----------------------------------------------------------------------------
set(SimVascular_DEPENDENCIES "")

include(${CMAKE_CURRENT_SOURCE_DIR}/External_VTK.cmake)
list(APPEND SimVascular_DEPENDENCIES VTK)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_GDCM.cmake)
list(APPEND SimVascular_DEPENDENCIES GDCM)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_HDF5.cmake)
list(APPEND SimVascular_DEPENDENCIES HDF5)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_ITK.cmake)
list(APPEND SimVascular_DEPENDENCIES ITK)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_OpenCASCADE.cmake)
list(APPEND SimVascular_DEPENDENCIES OpenCASCADE)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_MMG.cmake)
list(APPEND SimVascular_DEPENDENCIES MMG)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_TetGen.cmake)
list(APPEND SimVascular_DEPENDENCIES TetGen)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_tinyxml2.cmake)
list(APPEND SimVascular_DEPENDENCIES tinyxml2)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_VMTK.cmake)
list(APPEND SimVascular_DEPENDENCIES VMTK)

# include(${CMAKE_CURRENT_SOURCE_DIR}/External_MITK.cmake)
# list(APPEND SimVascular_DEPENDENCIES MITK)

#-----------------------------------------------------------------------------
# Arguments forwarded to the inner (non-superbuild) SimVascular configure
#-----------------------------------------------------------------------------
set(SimVascular_superbuild_ep_args
  -DSimVascular_SUPERBUILD:BOOL=OFF
  -DSV_WRAP_PYTHON:BOOL=${SV_WRAP_PYTHON}
  -DQt6_DIR:PATH=${Qt6_DIR}
  -DPython_EXECUTABLE:PATH=${Python_EXECUTABLE}
  -DPython3_EXECUTABLE:FILEPATH=${Python_EXECUTABLE}
  -DPython3_ROOT_DIR:PATH=${Python_ROOT_DIR}
  -DVTK_DIR:PATH=${VTK_DIR}
  -DGDCM_DIR:PATH=${GDCM_DIR}
  -DHDF5_DIR:PATH=${HDF5_DIR}
  -DITK_DIR:PATH=${ITK_DIR}
  # -DMITK_DIR:PATH=${MITK_DIR}
  -DOpenCASCADE_DIR:PATH=${OpenCASCADE_DIR}
  -DMMG_DIR:PATH=${MMG_DIR}
  -DMMG_INCLUDE_DIR:PATH=${MMG_INCLUDE_DIR}
  -DTETGEN_INCLUDE_DIR:PATH=${TETGEN_INCLUDE_DIR}
  -DTETGEN_LIBRARY:FILEPATH=${TETGEN_LIBRARY}
  -Dtinyxml2_DIR:PATH=${tinyxml2_DIR}
  -DVMTK_DIR:PATH=${VMTK_DIR}
)

ExternalProject_Add(SimVascular
  SOURCE_DIR ${CMAKE_SOURCE_DIR}
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SimVascular-build
  CMAKE_ARGS
    ${ep_common_cmake_args}
    ${SimVascular_superbuild_ep_args}
  INSTALL_COMMAND ""
  DEPENDS ${SimVascular_DEPENDENCIES}
)
