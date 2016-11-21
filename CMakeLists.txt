cmake_minimum_required(VERSION 2.8)

if(NOT ParaView_SOURCE_DIR)
  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
else()
  include_directories(
    ${PARAVIEW_INCLUDE_DIRS}
    ${PARAVIEW_KWSYS_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS}
  )
endif()

ADD_PARAVIEW_PLUGIN(PhastaSyncIOReader "1.0"
                                       SERVER_MANAGER_XML PhastaSyncIO.xml
                                       SERVER_MANAGER_SOURCES
                                       vtkPhastaSyncIOMetaReader.cxx
                                       vtkPhastaSyncIOReader.cxx
                                       REQUIRED_ON_SERVER
                                       )
