cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RtspRadio)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(RtspRadio src/main.cpp)

# Include directories
target_include_directories(RtspRadio PRIVATE include)