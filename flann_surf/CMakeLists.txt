cmake_minimum_required(VERSION 3.4)

project(FLANN_SURF)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(FLANN_SURF main.cpp)
target_link_libraries(FLANN_SURF ${OpenCV_LIBS})
