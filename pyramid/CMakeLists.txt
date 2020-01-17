cmake_minimum_required(VERSION 3.4)
project(pyramid)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories($OpenCV_INCLUDE_DIRS)


add_executable(pyramid main.cpp)
target_link_libraries(pyramid ${OpenCV_LIBS})