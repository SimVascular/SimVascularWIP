set(vtkSV4ModelCommon_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svCommonExports.h)
set(vtkSV4ModelCommon_HEADERS
    sv4gui_ModelDataInteractor.h
    sv4gui_ModelElementAnalytic.h
    sv4gui_RegisterPolyDataFunction.h
    sv4gui_ModelMarkerContainer.h
    sv4gui_ModelVtkMapper2D.h
    sv4gui_ModelUtils.h
    sv4gui_ModelIO.h
    sv4gui_ModelElementPolyData.h
    sv4gui_ModelOperation.h
    sv4gui_ModelElementFactory.h
    sv4gui_ModelElement.h
    sv4gui_ModelMarkerMapper.h
    sv4gui_ModelVtkMapper3D.h
    sv4gui_ModelObjectFactory.h
    sv4gui_ModelLegacyIO.h
    sv4gui_Model.h
    ${vtkSV4ModelCommon_EXPORT_HEADER}
)

set(vtkSV4ModelCommon_SOURCES
    sv4gui_ModelElementPolyData.cxx
    sv4gui_ModelVtkMapper3D.cxx
    sv4gui_ModelMarkerMapper.cxx
    sv4gui_RegisterPolyDataFunction.cxx
    sv4gui_ModelVtkMapper2D.cxx
    sv4gui_ModelElementAnalytic.cxx
    sv4gui_ModelObjectFactory.cxx
    sv4gui_ModelUtils.cxx
    sv4gui_ModelElement.cxx
    sv4gui_ModelOperation.cxx
    sv4gui_ModelLegacyIO.cxx
    sv4gui_ModelMarkerContainer.cxx
    sv4gui_ModelIO.cxx
    sv4gui_Model.cxx
    sv4gui_ModelElementFactory.cxx
    sv4gui_ModelDataInteractor.cxx
)

vtk_module_add_module(VTK::SV4ModelCommon
    HEADERS ${vtkSV4ModelCommon_HEADERS}
    SOURCES ${vtkSV4ModelCommon_SOURCES}
)
generate_export_header(VTK::SV4ModelCommon
    EXPORT_MACRO_NAME "SV_EXPORT_COMMON"
    EXPORT_FILE_NAME ${vtkSV4ModelCommon_EXPORT_HEADER}
)