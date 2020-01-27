cmake_minimum_required(VERSION 3.5)
project(5_4_3)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_executable(5_4_3 main.cpp)