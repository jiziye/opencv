cmake_minimum_required(VERSION 3.4)
project(surfdescrip)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(surfdescrip main.cpp)
target_link_libraries(surfdescrip ${OpenCV_LIBS})