cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(WriteVTU)

find_package(VTK COMPONENTS 
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersGeneral
  vtkIOXML
  vtkInteractionStyle)
  if (NOT VTK_FOUND)
  message("Skipping WriteVTU: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(WriteVTU MACOSX_BUNDLE WriteVTU.cxx )
  target_link_libraries(WriteVTU PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(WriteVTU MACOSX_BUNDLE WriteVTU.cxx )
  target_link_libraries(WriteVTU PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS WriteVTU
    MODULES ${VTK_LIBRARIES}
    )
endif () 
