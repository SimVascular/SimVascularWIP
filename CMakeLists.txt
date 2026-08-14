cmake_minimum_required(VERSION 3.20)

project(SimVascular
  VERSION 1.0.0
  LANGUAGES CXX C
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  # MSVC only defines M_PI/M_E/etc. from <cmath> when this is set; glibc/libc++
  # expose them unconditionally, which is why this was never needed elsewhere.
  add_compile_definitions(_USE_MATH_DEFINES)
endif()

# Find Python
find_package(Python 3.12...<3.13 COMPONENTS Interpreter Development.Module REQUIRED)

# Find Qt
find_package(Qt6 6.10 COMPONENTS Core CoreTools Gui Widgets Xml REQUIRED)

#-----------------------------------------------------------------------------
# Superbuild
#-----------------------------------------------------------------------------
option(SimVascular_SUPERBUILD "Build SimVascular and its external dependencies via CMake superbuild." ON)
mark_as_advanced(SimVascular_SUPERBUILD)

option(SV_WRAP_PYTHON "Build SimVascular Python Bindings" ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

if(SimVascular_SUPERBUILD)
  add_subdirectory(SuperBuild)
  return()
endif()

#-----------------------------------------------------------------------------
# The following is only executed when NOT building via the superbuild
#-----------------------------------------------------------------------------
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)

find_package(VMTK REQUIRED)

# find_package(MITK REQUIRED)

find_package(tinyxml2 REQUIRED)

find_package(OpenCASCADE REQUIRED)

find_package(Python3 3.12...<3.13 COMPONENTS Interpreter Development REQUIRED)
set(PYTHON_MAJOR_VERSION ${Python3_VERSION_MAJOR})

add_subdirectory(Source)
