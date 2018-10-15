cmake_minimum_required(VERSION 2.8)
project(VideoDisplay)

set(CMAKE_CXX_STANDARD 14)

add_executable(VideoDisplay main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( VideoDisplay ${OpenCV_LIBS} )
