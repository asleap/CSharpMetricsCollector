cmake_minimum_required(VERSION 3.6)
project(CSharpMetrics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# -g Write debug information -Wall Turn on all optional warnings -O0 No optimizations -Wno-deprecated-register ??
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -O0")

add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
