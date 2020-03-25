cmake_minimum_required(VERSION 3.4)
project(back_projection)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(back_projection main.cpp)
target_link_libraries(back_projection ${OpenCV_LIBS})