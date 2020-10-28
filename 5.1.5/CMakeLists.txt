cmake_minimum_required(VERSION 2.8)
project(5_1_5)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_executable(5_1_5 main.cpp)