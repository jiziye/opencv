cmake_minimum_required(VERSION 3.4)

project(perspectivetransform)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(perspectivetransform main.cpp)
target_link_libraries(perspectivetransform ${OpenCV_LIBS})
