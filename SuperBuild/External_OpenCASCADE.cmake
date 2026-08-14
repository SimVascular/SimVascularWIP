set(OpenCASCADE_VERSION "7.6.0")
set(OpenCASCADE_INSTALL_DIR ${CMAKE_BINARY_DIR}/OpenCASCADE-install)
set(OpenCASCADE_DIR ${OpenCASCADE_INSTALL_DIR}/lib/cmake/opencascade)

# OCCT's Visualization module requires FreeType. Linux/macOS normally find a
# system install via find_package(Freetype); Windows has none, so a vendored
# FreeType (see External_FreeType.cmake) is pointed to explicitly instead.
set(OpenCASCADE_FreeType_ARGS "")
set(OpenCASCADE_FreeType_DEPENDS "")
if(WIN32)
  set(OpenCASCADE_FreeType_ARGS
    -D3RDPARTY_FREETYPE_DIR:PATH=${FreeType_INSTALL_DIR}
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_ft2build:PATH=${FreeType_INSTALL_DIR}/include/freetype2
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_freetype2:PATH=${FreeType_INSTALL_DIR}/include/freetype2
    -D3RDPARTY_FREETYPE_LIBRARY:FILEPATH=${FreeType_INSTALL_DIR}/lib/freetype.lib
    -D3RDPARTY_FREETYPE_LIBRARY_DIR:PATH=${FreeType_INSTALL_DIR}/lib
    -D3RDPARTY_FREETYPE_DLL:FILEPATH=${FreeType_INSTALL_DIR}/bin/freetype.dll
    -D3RDPARTY_FREETYPE_DLL_DIR:PATH=${FreeType_INSTALL_DIR}/bin
  )
  set(OpenCASCADE_FreeType_DEPENDS FreeType)
endif()

ExternalProject_Add(OpenCASCADE
  GIT_REPOSITORY "https://github.com/Open-Cascade-SAS/OCCT.git"
  GIT_TAG        "V7_6_0"
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  SOURCE_DIR     ${CMAKE_CURRENT_BINARY_DIR}/OpenCASCADE
  BINARY_DIR     ${CMAKE_CURRENT_BINARY_DIR}/OpenCASCADE-build
  PATCH_COMMAND
    ${CMAKE_COMMAND}
      -DOpenCASCADE_SOURCE_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/OpenCASCADE
      -P ${CMAKE_CURRENT_SOURCE_DIR}/PatchOpenCASCADEMacOS.cmake
  CMAKE_ARGS
    ${ep_common_cmake_args}
    -DCMAKE_INSTALL_PREFIX:PATH=${OpenCASCADE_INSTALL_DIR}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_MODULE_Draw:BOOL=OFF
    -DBUILD_MODULE_Visualization:BOOL=ON
    -DBUILD_MODULE_ApplicationFramework:BOOL=ON
    -DBUILD_TESTING:BOOL=OFF
    -DUSE_VTK:BOOL=ON
    -D3RDPARTY_VTK_DIR:PATH=${VTK_INSTALL_DIR}
    -D3RDPARTY_VTK_INCLUDE_DIR:PATH=${VTK_INSTALL_DIR}/include/vtk-9.3
    -D3RDPARTY_VTK_LIBRARY_DIR:PATH=${VTK_INSTALL_DIR}/lib
    -DINSTALL_DIR_LIB:STRING=lib
    -DINSTALL_DIR_INCLUDE:STRING=include/opencascade
    -DINSTALL_DIR_CMAKE:STRING=lib/cmake/opencascade
    -DINSTALL_DIR_BIN:STRING=bin
    ${OpenCASCADE_FreeType_ARGS}
  INSTALL_DIR ${OpenCASCADE_INSTALL_DIR}
  DEPENDS VTK ${OpenCASCADE_FreeType_DEPENDS}
  USES_TERMINAL_DOWNLOAD 1
  USES_TERMINAL_UPDATE   1
  USES_TERMINAL_BUILD    1
)
