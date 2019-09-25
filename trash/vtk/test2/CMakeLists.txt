cmake_minimum_required(VERSION 2.8)

PROJECT(testMain)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(testMain MACOSX_BUNDLE testMain.cxx ${SOURCES})

if(VTK_LIBRARIES)
	target_link_libraries(testMain ${SOURCES} ${VTK_LIBRARIES})
else()
	target_link_libraries(testMain ${SOURCES} vtkHybrid vtkWidgets)
endif()
