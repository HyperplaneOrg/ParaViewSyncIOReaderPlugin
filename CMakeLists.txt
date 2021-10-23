cmake_minimum_required(VERSION 3.8)
project(PhastaSyncIOReader)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

if(NOT ParaView_SOURCE_DIR)
  find_package(ParaView REQUIRED)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
else()
  include_directories(
    ${PARAVIEW_INCLUDE_DIRS}
    ${PARAVIEW_KWSYS_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS}
  )
endif()

#ADD_PARAVIEW_PLUGIN(PhastaSyncIOReader "1.0"
#                                       SERVER_MANAGER_XML PhastaSyncIO.xml
#                                       SERVER_MANAGER_SOURCES
#                                       vtkPhastaSyncIOMetaReader.cxx
#                                       vtkPhastaSyncIOReader.cxx
#                                       REQUIRED_ON_SERVER
#                                       )


set("_paraview_plugin_default_${CMAKE_PROJECT_NAME}" ON)
paraview_plugin_scan(
	PLUGIN_FILES	"${CMAKE_CURRENT_SOURCE_DIR}/Plugin/paraview.plugin"
	PROVIDES_PLUGINS plugins
	REQUIRES_MODULES required_modules)

message(${plugins})
paraview_plugin_build(
	#RUNTIME_DESTINATION "${CMAKE_INSTALL_BINDIR}"
	#	LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	#LIBRARY_SUBDIRECTORY "${PARAVIEW_PLUGIN_SUBDIR}"
	PLUGINS ${plugins})
