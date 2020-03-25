cmake_minimum_required(VERSION 3.5)
project(convexHull)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(convexHull main.cpp)
target_link_libraries(convexHull ${OpenCV_LIBS})

