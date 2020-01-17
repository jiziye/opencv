cmake_minimum_required(VERSION 3.4)
project(houghcircles)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(houghcircles main.cpp)
target_link_libraries(houghcircles ${OpenCV_LIBS})