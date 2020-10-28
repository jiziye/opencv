cmake_minimum_required(VERSION 3.4)
project(6_6_7)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_executable(6_6_7 main.cpp)
target_link_libraries(6_6_7 ${OpenCV_LIBS})
