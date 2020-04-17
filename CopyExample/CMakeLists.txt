# NE 697 Geant4 CMake file
# Create by Micah Folsom
# August 9, 2017
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(CopyExample)

# Geant4 setup - check for visualization
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})

# ne697g4 setup
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -pedantic -fPIC -pthread -m64 -std=c++11")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(OUTPUT_SCRIPTS_DIR ${PROJECT_BINARY_DIR}/scripts)

# create libne697g4.so and the binary, NE697G4
add_library(ne697g4 SHARED ${SOURCES})
target_link_libraries(ne697g4 ${CMAKE_CXX_FLAGS} ${Geant4_LIBRARIES})
# Sim application
add_executable(NE697G4 ${PROJECT_SOURCE_DIR}/src/ne697g4.cc)
target_link_libraries(NE697G4 ${CMAKE_CXX_FLAGS} ne697g4 ${Geant4_LIBRARIES})

# Copy the scripts to the build directory
file(COPY ${SCRIPTS} DESTINATION ${OUTPUT_SCRIPTS_DIR})
