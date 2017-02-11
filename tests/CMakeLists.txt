cmake_minimum_required(VERSION 3.6)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/flex)
include_directories(${PROJECT_SOURCE_DIR}/src/generated)

set(SOURCE_FILES ParserTests.cpp)

add_executable(RunTests ${SOURCE_FILES})

target_link_libraries(RunTests gtest gtest_main)
target_link_libraries(RunTests CSharpMetricsLib)