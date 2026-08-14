set(FreeType_VERSION "2.13.3")
set(FreeType_INSTALL_DIR ${CMAKE_BINARY_DIR}/FreeType-install)

# OpenCASCADE's Visualization module (font/text rendering) hard-requires
# FreeType. On Linux/macOS this is normally satisfied by a system FreeType
# dev package, but Windows has no equivalent, so FreeType is vendored here
# (Windows-only, see External_OpenCASCADE.cmake) rather than relying on
# find_package(Freetype) finding nothing.
ExternalProject_Add(FreeType
  GIT_REPOSITORY "https://github.com/freetype/freetype.git"
  GIT_TAG        "VER-2-13-3"
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  SOURCE_DIR     ${CMAKE_CURRENT_BINARY_DIR}/FreeType
  BINARY_DIR     ${CMAKE_CURRENT_BINARY_DIR}/FreeType-build
  CMAKE_ARGS
    ${ep_common_cmake_args}
    -DCMAKE_INSTALL_PREFIX:PATH=${FreeType_INSTALL_DIR}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DFT_DISABLE_ZLIB:BOOL=ON
    -DFT_DISABLE_BZIP2:BOOL=ON
    -DFT_DISABLE_PNG:BOOL=ON
    -DFT_DISABLE_HARFBUZZ:BOOL=ON
    -DFT_DISABLE_BROTLI:BOOL=ON
  INSTALL_DIR ${FreeType_INSTALL_DIR}
  USES_TERMINAL_DOWNLOAD 1
  USES_TERMINAL_UPDATE   1
  USES_TERMINAL_BUILD    1
)
