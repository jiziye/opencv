cmake_minimum_required(VERSION 3.5)
project(open_mynteye)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(open_mynteye  main.cpp)
target_link_libraries(open_mynteye ${OpenCV_LIBS})