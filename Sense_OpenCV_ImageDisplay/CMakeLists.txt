cmake_minimum_required(VERSION 2.8)
project(OpenCVImageDisplay)

set(CMAKE_CXX_STANDARD 14)

add_executable(OpenCVImageDisplay main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( OpenCVImageDisplay ${OpenCV_LIBS} )