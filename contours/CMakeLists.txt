cmake_minimum_required(VERSION 3.4)
project(contours)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(contours main.cpp)

target_link_libraries(contours ${OpenCV_LIBS})
