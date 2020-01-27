cmake_minimum_required(VERSION 3.4)
project(6_1_12)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_executable(6_1_12 main.cpp)