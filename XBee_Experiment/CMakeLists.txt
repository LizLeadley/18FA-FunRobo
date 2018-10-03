cmake_minimum_required(VERSION 3.12)
project(XBee_Experiment)

set(CMAKE_CXX_STANDARD 14)

add_executable(XBee_Experiment main.cpp Serial.cpp SerialClass.h)