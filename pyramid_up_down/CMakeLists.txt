cmake_minimum_required(VERSION 3.4)
project(pyramid_up_down)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(pyramid_up_down main.cpp)
target_link_libraries(pyramid_up_down ${OpenCV_LIBS})

