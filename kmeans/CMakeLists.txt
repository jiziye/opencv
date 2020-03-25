cmake_minimum_required(VERSION 3.4)

project(kmeans)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_LIBS})

add_executable(kmeans main.cpp)
target_link_libraries(kmeans ${OpenCV_LIBS})


