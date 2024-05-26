cmake_minimum_required(VERSION 3.15)

# Set the project name and C++ standard
project(MyCppProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files
include_directories(include)

# Add the executable
add_executable(MyCppProject main.cpp)
