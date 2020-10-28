cmake_minimum_required(VERSION 3.4)
project(watermeter_rec)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(/usr/include/leptonica  /usr/include/tesseract)

add_executable(watermeter_rec main2.cpp)
target_link_libraries(watermeter_rec  ${OpenCV_LIBS} ${tesseract_LIBS}  tesseract  lept)
