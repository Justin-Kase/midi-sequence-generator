cmake_minimum_required(VERSION 3.21)
project(MidiSequenceGenerator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch JUCE
include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 7.0.12 # Known stable as of 2025-10; adjust if needed
)
FetchContent_MakeAvailable(juce)

# Enable VST3 only, no AU to keep it simple
option(BUILD_AU "Build AudioUnit" OFF)

add_subdirectory(Source)
