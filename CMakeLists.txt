cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(paintApp VERSION 1.0.0)

include_directories(include app/include)

set (SOURCE src/Circle.cpp src/Rectangle.cpp)

add_executable(paintApp 
               ${SOURCE}
               app/src/Paint.cpp)

# cmake -G "MinGW Makefiles" -S . -B build
