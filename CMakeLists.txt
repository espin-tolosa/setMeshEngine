cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
enable_language(CXX)
project(main CXX)

file(GLOB_RECURSE Foo_SOURCES "src/functions/*.cpp" "src/geometry/*.cpp" "src/logs/*.cpp" "src/materials/*.cpp" "src/maths/*.cpp" "src/phase/*.cpp" "src/vtk/*.cpp" "main.cpp" )
file(GLOB_RECURSE Foo_HEADERS  "src/*.h" "lib/*.h" "constants/*.h" "src/functions/*.h" "src/geometry/*.h" "src/logs/*.h" "src/materials/*.h" "src/maths/*.h" "src/phase/*.h" "src/vtk/*.h" )

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
  vtkInteractionStyle QUIET)

if (NOT VTK_FOUND)
  message("Skipping main: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(main MACOSX_BUNDLE ${Foo_INCLUDE_DIRS})
  #  target_compile_options(main PUBLIC -std=c++11 -fpermisive -w -Wall)
  target_link_libraries(main PRIVATE ${VTK_LIBRARIES})
  target_include_directories(main PRIVATE ${Foo_INCLUDE_DIRS})
else ()
  # include all components
  add_executable(main MACOSX_BUNDLE ${Foo_INCLUDE_DIRS} )
  #target_compile_options(main PUBLIC -std=c++11 -fpermisive -w -Wall)
  target_link_libraries(main PRIVATE ${VTK_LIBRARIES})
  target_include_directories(main PRIVATE ${Foo_INCLUDE_DIRS})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS main
    MODULES ${VTK_LIBRARIES}
    )
endif () 
