cmake_minimum_required(VERSION 3.11.0)
project(cpp_options CXX)

# Enable C+11
set(CMAKE_CXX_STANDARD 14)

# Library source files
file(GLOB LIB_SOURCES src/*.cc src/examples/*.cc)
file(GLOB LIB_HEADERS include/*.h src/examples/*.h)
add_library(cpp_options ${LIB_SOURCES} ${LIB_HEADERS})

include_directories("${CMAKE_SOURCE_DIR}/include")

# Create example executable
add_executable(example src/main.cc)
target_link_libraries(example cpp_options)

