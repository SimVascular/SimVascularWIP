set(brep_font_cxx "${OpenCASCADE_SOURCE_DIR}/src/StdPrs/StdPrs_BRepFont.cxx")

if(NOT EXISTS "${brep_font_cxx}")
  message(FATAL_ERROR "Unable to find OpenCASCADE BRep font source: ${brep_font_cxx}")
endif()

file(READ "${brep_font_cxx}" brep_font_cxx_contents)

set(old_tags_line "const char* aTags      = &anOutline->tags[aStartIndex];")
set(new_tags_line "const char* aTags      = reinterpret_cast<const char*>(&anOutline->tags[aStartIndex]);")

if(brep_font_cxx_contents MATCHES "const char\\* aTags[ ]*= &anOutline->tags\\[aStartIndex\\];")
  string(REPLACE "${old_tags_line}" "${new_tags_line}" brep_font_cxx_contents "${brep_font_cxx_contents}")
  file(WRITE "${brep_font_cxx}" "${brep_font_cxx_contents}")
elseif(NOT brep_font_cxx_contents MATCHES "const char\\* aTags[ ]*= reinterpret_cast<const char\\*>\\(&anOutline->tags\\[aStartIndex\\]\\);")
  message(FATAL_ERROR "OpenCASCADE FreeType outline tag patch no longer matches ${brep_font_cxx}")
endif()
