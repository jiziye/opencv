cmake_minimum_required(VERSION 2.8)
project(OCVSamples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV 3.0 QUIET)
if(OpenCV_FOUND)
  add_definitions(-DUSE_OPENCV3)
else()
  message(FATAL_ERROR "OpenCV > 3.0 not found.")
endif()

option(USE_OPENNI "Use OpenNI" ON)

if(USE_OPENNI)
  add_definitions(-DUSE_OPENNI)
endif()

include_directories(
  common
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)

add_executable(camera "camera.cc")
target_link_libraries(camera ${OpenCV_LIBS})
