cmake_minimum_required(VERSION 3.5)
project(inpaint)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable(inpaint main.cpp)
target_link_libraries(inpaint ${OpenCV_LIBS})