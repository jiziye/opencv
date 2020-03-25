cmake_minimum_required(VERSION 3.4)
project(defect_detect)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(defect_detect main.cpp)
target_link_libraries(defect_detect ${OpenCV_LIBS})