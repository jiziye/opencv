cmake_minimum_required(VERSION 3.4)
project(affine_transformation)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(affine_transformation main.cpp)

target_link_libraries(affine_transformation ${OpenCV_LIBS})