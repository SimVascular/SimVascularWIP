set(vtkSV3Common_HEADERS
    sv3_XmlIOUtil.h
)

set(vtkSV3Common_SOURCES
    sv3_XmlIOUtil.cxx
)

vtk_module_add_module(VTK::SV3Common
    HEADERS ${vtkSV3Common_HEADERS}
    SOURCES ${vtkSV3Common_SOURCES}
)

vtk_module_link(VTK::SV3Common PUBLIC tinyxml2)  # todo superbuild