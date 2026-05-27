cmake_minimum_required(VERSION 3.20)

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
  -DBUILD_TESTING:BOOL=OFF
)

#-----------------------------------------------------------------------------
# External dependencies
#-----------------------------------------------------------------------------
set(SimVascular_DEPENDENCIES "")

include(${CMAKE_CURRENT_SOURCE_DIR}/External_VTK.cmake)
list(APPEND SimVascular_DEPENDENCIES VTK)

include(${CMAKE_CURRENT_SOURCE_DIR}/External_ITK.cmake)
list(APPEND SimVascular_DEPENDENCIES ITK)

#-----------------------------------------------------------------------------
# Arguments forwarded to the inner (non-superbuild) SimVascular configure
#-----------------------------------------------------------------------------
set(SimVascular_superbuild_ep_args
  -DSimVascular_SUPERBUILD:BOOL=OFF
  -DVTK_DIR:PATH=${VTK_DIR}
  -DITK_DIR:PATH=${ITK_DIR}
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
