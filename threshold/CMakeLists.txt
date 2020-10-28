cmake_minimum_required(VERSION 3.4)
project(threshold)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
add_executable(threshold main.cpp)
target_link_libraries(threshold ${OpenCV_LIBS})