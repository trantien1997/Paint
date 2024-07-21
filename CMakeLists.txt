cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(paintApp VERSION 1.0.0)

add_include_directories(include)

add_executable(paintApp app/src/main.cpp src/Circle.cpp src/Rectangle.cpp)

# cmake -G "MinGW Makefiles" -S . -B build
