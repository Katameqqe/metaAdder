cmake_minimum_required(VERSION 3.10)
project(MetaAdder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively find all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable from all source files
add_executable(app ${SOURCES})

# Optionally, set the output directory for the binary
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)