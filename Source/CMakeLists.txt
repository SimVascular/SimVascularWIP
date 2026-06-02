set(VTK_GROUP_ENABLE_SV "YES")

vtk_module_find_modules(module_files "${CMAKE_CURRENT_SOURCE_DIR}")
vtk_module_scan(
        MODULE_FILES ${module_files}
        PROVIDES_MODULES modules
)
vtk_module_build(
        MODULES ${modules}
        INSTALL_EXPORT VTKSV
)
