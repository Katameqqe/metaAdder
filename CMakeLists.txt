cmake_minimum_required(VERSION 3.10)
project(MetaAdder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively find all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBZIP REQUIRED libzip)

# include_directories(${LIBZIP_INCLUDE_DIRS})
# link_directories(${LIBZIP_LIBRARY_DIRS})

# Create the executable from all source files
add_executable(app ${SOURCES})

target_link_libraries(app ${LIBZIP_LIBRARIES})

# Optionally, set the output directory for the binary
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)