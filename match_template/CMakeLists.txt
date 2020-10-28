cmake_minimum_required(VERSION 3.4)
project(match_template)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(match_template main.cpp)
target_link_libraries(match_template ${OpenCV_LIBS})