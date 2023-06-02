
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(MiceOldSetup)
#set(CMAKE_CXX_STANDARD 14)


#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build MiceOldSetup with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${Geant4_dir}/Modules)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(MiceOldSetup MiceOldSetup.cc ${sources} ${headers})
target_link_libraries(MiceOldSetup ${Geant4_LIBRARIES})

foreach(_script ${MiceOldSetup_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )

#file(COPY SOBP DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY Output DESTINATION ${CMAKE_BINARY_DIR})

endforeach()
