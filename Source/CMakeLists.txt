# group SV1
set(VTK_MODULE_ENABLE_VTK_SV1Geometry "YES")
set(VTK_MODULE_ENABLE_VTK_SV1MeshAdaptObject "YES")
#set(VTK_MODULE_ENABLE_VTK_SV1MeshMMGMeshUtils "YES")  # disabled due to mmg
set(VTK_MODULE_ENABLE_VTK_SV1MeshMeshObject "YES")
#set(VTK_MODULE_ENABLE_VTK_SV1MeshTetGenAdapt "YES")  # disabled due to tetgen
#set(VTK_MODULE_ENABLE_VTK_SV1MeshTetGenMeshObject "YES")  # disabled due to tetgen
#set(VTK_MODULE_ENABLE_VTK_SV1MeshVMTKUtils "YES")  # disabled due to vmtk
#set(VTK_MODULE_ENABLE_VTK_SV1ModelOCCTSolidModel "YES")  # disabled due to opencascade
set(VTK_MODULE_ENABLE_VTK_SV1ModelPolyDataSolidModel "YES")
set(VTK_MODULE_ENABLE_VTK_SV1ModelSolidModel "YES")
set(VTK_MODULE_ENABLE_VTK_SV1Repository "YES")
set(VTK_MODULE_ENABLE_VTK_SV1Utils "YES")

# group SV2
set(VTK_MODULE_ENABLE_VTK_SV2ImageProcessing "YES")
set(VTK_MODULE_ENABLE_VTK_SV2PostProcessing "YES")

# group SV3
set(VTK_MODULE_ENABLE_VTK_SV3Common "YES")
set(VTK_MODULE_ENABLE_VTK_SV3ITKSegmentation "YES")
set(VTK_MODULE_ENABLE_VTK_SV3Path "YES")
set(VTK_MODULE_ENABLE_VTK_SV3Segmentation "YES")

# group SV4
set(VTK_MODULE_ENABLE_VTK_SV4Common "YES")
set(VTK_MODULE_ENABLE_VTK_SV4ImageProcessing "YES")
set(VTK_MODULE_ENABLE_VTK_SV4MachineLearning "YES")
#set(VTK_MODULE_ENABLE_VTK_SV4MeshCommon "YES")  # disabled due to tetgen
#set(VTK_MODULE_ENABLE_VTK_SV4ModelCommon "YES")  # disabled due to tetgen
#set(VTK_MODULE_ENABLE_VTK_SV4ModelOCCT "YES")  # disabled due to tetgen, opencascade
set(VTK_MODULE_ENABLE_VTK_SV4MultiPhysics "YES")
set(VTK_MODULE_ENABLE_VTK_SV4Path "YES")
#set(VTK_MODULE_ENABLE_VTK_SV4ProjectManagement "YES")  # disabled due to i dont want to
#set(VTK_MODULE_ENABLE_VTK_SV4QtWidgets "YES")  # disabled due to i dont want to
set(VTK_MODULE_ENABLE_VTK_SV4ROMSimulation "YES")
set(VTK_MODULE_ENABLE_VTK_SV4Segmentation "YES")
#set(VTK_MODULE_ENABLE_VTK_SV4Simulation "YES")  # disabled due to plugin dependency org.sv.gui.qt.simulation

# group VTKSV
set(VTK_MODULE_ENABLE_VTK_SVBoolean "YES")
set(VTK_MODULE_ENABLE_VTK_SVCommon "YES")
set(VTK_MODULE_ENABLE_VTK_SVGeometry "YES")
set(VTK_MODULE_ENABLE_VTK_SVIO "YES")
set(VTK_MODULE_ENABLE_VTK_SVInclude "YES")
set(VTK_MODULE_ENABLE_VTK_SVMisc "YES")
set(VTK_MODULE_ENABLE_VTK_SVNURBS "YES")
set(VTK_MODULE_ENABLE_VTK_SVParameterization "YES")
#set(VTK_MODULE_ENABLE_VTK_SVSegmentation "YES")  # disabled due to vmtk

vtk_module_find_modules(module_files "${CMAKE_CURRENT_SOURCE_DIR}")
vtk_module_scan(
        MODULE_FILES ${module_files}
        PROVIDES_MODULES modules
)
vtk_module_build(
        MODULES ${modules}
        INSTALL_EXPORT VTKSV
)
