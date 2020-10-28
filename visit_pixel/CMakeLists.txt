cmake_minimum_required(VERSION 3.4)
project(visit_pixel)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories($OpenCV_INCLUDE_DIRS})

add_executable(visit_pixel main.cpp)
target_link_libraries(visit_pixel ${OpenCV_LIBS})