cmake_minimum_required(VERSION 3.5)
project(open_stereo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(include)

include_directories( ${OpenCV_INCLUDE_DIRS})
add_executable(open_stereo main.cc)
target_link_libraries(open_stereo ${OpenCV_LIBS})