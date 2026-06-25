cmake_minimum_required(VERSION 3.10)
project(OneRail VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory
include_directories(include)

# Define source files for the core library
set(CORE_SOURCES
    src/coach.cpp
    src/train.cpp
    src/waitlist.cpp
    src/booking_engine.cpp
)

# Create a library for the core logic
add_library(onerail_core ${CORE_SOURCES})

# Create the executable for the demonstration
add_executable(onerail_demo src/main.cpp)
target_link_libraries(onerail_demo PRIVATE onerail_core)
