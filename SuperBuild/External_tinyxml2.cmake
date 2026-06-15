set(tinyxml2_VERSION "10.0.0")
set(tinyxml2_INSTALL_DIR ${CMAKE_BINARY_DIR}/tinyxml2-install)
set(tinyxml2_DIR ${tinyxml2_INSTALL_DIR}/lib/cmake/tinyxml2)

ExternalProject_Add(tinyxml2
  GIT_REPOSITORY "https://github.com/leethomason/tinyxml2.git"
  GIT_TAG        "${tinyxml2_VERSION}"
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  SOURCE_DIR     ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2
  BINARY_DIR     ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-build
  CMAKE_ARGS
    ${ep_common_cmake_args}
    -DCMAKE_INSTALL_PREFIX:PATH=${tinyxml2_INSTALL_DIR}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -Dtinyxml2_BUILD_TESTING:BOOL=OFF
  INSTALL_DIR ${tinyxml2_INSTALL_DIR}
  USES_TERMINAL_DOWNLOAD 1
  USES_TERMINAL_UPDATE   1
  USES_TERMINAL_BUILD    1
)
