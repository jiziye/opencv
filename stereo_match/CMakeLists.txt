# cmake needs this line
cmake_minimum_required(VERSION 3.0)

# Define project name
project(stereo_match)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# set( PCL_DIR "/usr/local/share/pcl-1.7/" )
find_package(PCL REQUIRED COMPONENTS common io)
if(PCL_FOUND)
    include_directories( ${PCL_INCLUDE_DIRS} )
    add_definitions( ${PCL_DEFINITIONS} )
endif()
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
  # Add OpenCV headers location to your include paths
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

# Declare the executable target built from your sources
add_executable(stereo_match stereo_match.cpp)

# Link your application with OpenCV libraries
target_link_libraries(stereo_match ${OpenCV_LIBS} ${PCL_LIBRARIES})
