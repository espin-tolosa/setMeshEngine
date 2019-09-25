cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(main)
include_directories(${PROJECT_SOURCE_DIR})

#file(GLOB_RECURSE  Foo_SOURCES 	"main.cxx" "src/functions/*.cxx" "geometry/*.cxx" "src/logs/*.cxx" "src/materials/*.cxx" "src/maths/*.cxx" "src/phase/*.cxx" "src/vtk/*.cxx" )

#file(GLOB_RECURSE Foo_HEADERS "sources/*.h")

set(Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

find_package(VTK COMPONENTS 
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersGeneral
  vtkIOXML
  vtkInteractionStyle)
  if (NOT VTK_FOUND)
  message("Skipping main: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  add_executable(main main.cxx	vec3.cxx
				eos.cxx
				gas.cxx
				log.cxx
				octreeSHM.cxx
				phase.cxx
				setfun.cxx
				structuredHexMesh.cxx
				vec3.cxx
				vec3operations.cxx
				writeVTU.cxx
	  	 )
  #	  ${Foo_INCLUDE_DIRS})
  include(${VTK_USE_FILE})
  target_link_libraries(main PRIVATE ${VTK_LIBRARIES})
  #    target_include_directories(main PRIVATE ${Foo_INCLUDE_DIRS})
else ()
  # include all components
  add_executable(main main.cxx	vec3.cxx
				eos.cxx
				gas.cxx
				log.cxx
				octreeSHM.cxx
				phase.cxx
				setfun.cxx
				structuredHexMesh.cxx
				vec3.cxx
				vec3operations.cxx
				writeVTU.cxx
	  	 )
  #	${Foo_INCLUDE_DIRS})
  target_link_libraries(main PRIVATE ${VTK_LIBRARIES})
  #  target_include_directories(main PRIVATE ${Foo_INCLUDE_DIRS})
# vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS main
    MODULES ${VTK_LIBRARIES}
    )
endif ()
