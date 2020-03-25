cmake_minimum_required(VERSION 3.4)
project(histogram)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(histogram main.cpp)
target_link_libraries(histogram ${OpenCV_LIBS})