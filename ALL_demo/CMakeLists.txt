cmake_minimum_required(VERSION 3.5)
project(all_demo)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(all_demo main.cpp)
target_link_libraries(all_demo ${OpenCV_LIBS})