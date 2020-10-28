cmake_minimum_required(VERSION 3.4)

project(flann)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(flann main.cpp)
target_link_libraries(flann ${OpenCV_LIBS})

