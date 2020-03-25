cmake_minimum_required(VERSION 3.4)

project(BF_SIFT)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(BF_SIFT main.cpp)
target_link_libraries(BF_SIFT ${OpenCV_LIBS})


