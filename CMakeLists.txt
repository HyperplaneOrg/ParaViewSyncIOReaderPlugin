cmake_minimum_required(VERSION 2.8)

find_package(ParaView REQUIRED)
include(${PARAVIEW_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
ADD_PARAVIEW_PLUGIN(PhastaSyncIOReader "1.0"
					SERVER_MANAGER_XML PhastaSyncIO.xml
					SERVER_MANAGER_SOURCES
					vtkPhastaSyncIOMetaReader.cxx
					vtkPhastaSyncIOReader.cxx 
					)
