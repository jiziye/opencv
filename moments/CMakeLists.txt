cmake_minimum_required(VERSION 3.5)
project(moments)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(moments main.cpp)
target_link_libraries(moments ${OpenCV_LIBS})