cmake_minimum_required(VERSION 3.4)
project(resize_pyr)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(resize_pyr main.cpp)
target_link_libraries(resize_pyr ${OpenCV_LIBS})