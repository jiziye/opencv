cmake_minimum_required(VERSION 3.4)
project(harris)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(harris main.cpp)
target_link_libraries(harris ${OpenCV_LIBS})