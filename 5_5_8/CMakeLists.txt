cmake_minimum_required(VERSION 3.5)
project(5_5_8)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

set(CMAKE_BUILD_TYPE Debug)

add_definitions("-g")

add_executable(5_5_8 main.cpp)

