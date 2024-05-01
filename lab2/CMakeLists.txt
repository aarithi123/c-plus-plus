cmake_minimum_required(VERSION 3.27)
project(Lab_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_2 main.cpp
        Vehicle.cpp
        Vehicle.h
        Showroom.cpp
        Showroom.h
        Dealership.cpp
        Dealership.h)
