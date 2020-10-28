cmake_minimum_required(VERSION 3.5)
project(dil_ero)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(dil_ero main.cpp)
target_link_libraries(dil_ero ${OpenCV_LIBS})