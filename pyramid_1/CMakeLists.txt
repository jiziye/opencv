cmake_minimum_required(VERSION 3.4)
project(pyramid_1)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories($OpenCV_INCLUDE_DIRS)

add_executable(pyramid_1 main.cpp)
target_link_libraries(pyramid_1 ${OpenCV_LIBS})