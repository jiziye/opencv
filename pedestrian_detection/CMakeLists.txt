cmake_minimum_required(VERSION 3.5)
project(pedestrian_detection)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(include)

include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(pedestrian_detection main.cpp)
target_link_libraries(pedestrian_detection ${OpenCV_LIBS})