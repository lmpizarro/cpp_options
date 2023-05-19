cmake_minimum_required(VERSION 3.18.0)
project(cpp_options CXX)

# Enable C+11
set(CMAKE_CXX_STANDARD 17)

# Library source files
file(GLOB LIB_SOURCES src/*.cc src/examples/*.cc src/rofex/*.cc)
file(GLOB LIB_HEADERS include/*.h src/examples/*.h src/rofex/*.h)
add_library(cpp_options ${LIB_SOURCES} ${LIB_HEADERS})

include_directories("${CMAKE_SOURCE_DIR}/include")


find_package(cpr REQUIRED)
add_executable(example src/main.cc)
target_link_libraries(example PRIVATE cpp_options)
target_link_libraries(example PRIVATE cpr::cpr)

