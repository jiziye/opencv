cmake_minimum_required(VERSION 3.5)
project(5_3_3)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(5_3_3 main.cpp)
target_link_libraries(5_3_3 ${OpenCV_LIBS})