cmake_minimum_required(VERSION 3.4)

project(equalizeHist)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(equalizeHist main.cpp)
target_link_libraries(equalizeHist ${OpenCV_LIBS})

