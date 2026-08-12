set(zutil_h "${VTK_SOURCE_DIR}/ThirdParty/zlib/vtkzlib/zutil.h")
set(pngpriv_h "${VTK_SOURCE_DIR}/ThirdParty/png/vtkpng/pngpriv.h")
set(octree_node_txx "${VTK_SOURCE_DIR}/Utilities/octree/octree/octree_node.txx")

if(NOT EXISTS "${zutil_h}")
  message(FATAL_ERROR "Unable to find VTK zlib header: ${zutil_h}")
endif()

if(NOT EXISTS "${pngpriv_h}")
  message(FATAL_ERROR "Unable to find VTK png header: ${pngpriv_h}")
endif()

if(NOT EXISTS "${octree_node_txx}")
  message(FATAL_ERROR "Unable to find VTK octree header: ${octree_node_txx}")
endif()

file(READ "${zutil_h}" zutil_h_contents)

set(old_condition "#if defined(MACOS) || defined(TARGET_OS_MAC)")
set(new_condition "#if defined(MACOS) && !defined(__APPLE__)")

if(zutil_h_contents MATCHES "#if defined\\(MACOS\\) \\|\\| defined\\(TARGET_OS_MAC\\)")
  string(REPLACE "${old_condition}" "${new_condition}" zutil_h_contents "${zutil_h_contents}")
  file(WRITE "${zutil_h}" "${zutil_h_contents}")
elseif(NOT zutil_h_contents MATCHES "#if defined\\(MACOS\\) && !defined\\(__APPLE__\\)")
  message(FATAL_ERROR "VTK zlib macOS fdopen patch no longer matches ${zutil_h}")
endif()

file(READ "${pngpriv_h}" pngpriv_h_contents)

set(old_png_condition "defined(THINK_C) || defined(__SC__) || defined(TARGET_OS_MAC)")
set(new_png_condition "defined(THINK_C) || defined(__SC__) || (defined(TARGET_OS_MAC) && !defined(__APPLE__))")

if(pngpriv_h_contents MATCHES "defined\\(THINK_C\\) \\|\\| defined\\(__SC__\\) \\|\\| defined\\(TARGET_OS_MAC\\)")
  string(REPLACE "${old_png_condition}" "${new_png_condition}" pngpriv_h_contents "${pngpriv_h_contents}")
  file(WRITE "${pngpriv_h}" "${pngpriv_h_contents}")
elseif(NOT pngpriv_h_contents MATCHES "defined\\(THINK_C\\) \\|\\| defined\\(__SC__\\) \\|\\| \\(defined\\(TARGET_OS_MAC\\) && !defined\\(__APPLE__\\)\\)")
  message(FATAL_ERROR "VTK png macOS fp.h patch no longer matches ${pngpriv_h}")
endif()

file(READ "${octree_node_txx}" octree_node_txx_contents)

if(octree_node_txx_contents MATCHES "_M_chilren")
  string(REPLACE "_M_chilren" "m_children" octree_node_txx_contents "${octree_node_txx_contents}")
  file(WRITE "${octree_node_txx}" "${octree_node_txx_contents}")
elseif(NOT octree_node_txx_contents MATCHES "return this->m_children\\[child\\];")
  message(FATAL_ERROR "VTK octree child accessor patch no longer matches ${octree_node_txx}")
endif()
