cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RtspRadio)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(rtsp_radio)
set(SOURCE
  PRIVATE
  src/main.cpp
)

# include the imports
set(ARG_PARSER ${CMAKE_CURRENT_SOURCE_DIR}/imports/argparse/include)

# Include directories
target_include_directories(rtsp_radio
  PRIVATE
  ${ARG_PARSER}
)

target_sources(rtsp_radio
  ${SOURCE}
)

install(TARGETS rtsp_radio DESTINATION /usr/bin)
