cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name
project(RtspRadio C CXX)

# include the imports
set(ARG_PARSER ${CMAKE_CURRENT_SOURCE_DIR}/imports/argparse/include)

# Add subdirectories
add_executable(rtsp_radio)
set(SOURCE
  PRIVATE

  src/main.cpp

  src/player/player.cpp

  src/utils/file_selector.cpp
)

# Include directories
target_include_directories(rtsp_radio
  PRIVATE
  ${ARG_PARSER}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(rtsp_radio
  ${SOURCE}
)

install(TARGETS rtsp_radio DESTINATION /usr/bin)