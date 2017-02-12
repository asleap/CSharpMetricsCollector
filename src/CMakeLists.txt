cmake_minimum_required(VERSION 3.6)
project(CSharpMetrics)

# Create directory for generated files (for CMAKE_CURRENT_SOURCE_DIR only)
add_custom_target(CreateFlexBisonGeneratedDirectory ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory generated
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Creating directory: ${CMAKE_CURRENT_SOURCE_DIR}/generated")

# Bison settings
find_package(BISON 3.0)
if(BISON_FOUND)
    BISON_TARGET(CSParser bison/CSParser.ypp
            ${CMAKE_CURRENT_SOURCE_DIR}/generated/CSParser.cc
            DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/generated/CSParser.hh
            VERBOSE ${CMAKE_CURRENT_SOURCE_DIR}/generated)
    if(BISON_CSParser_DEFINED)
        message(STATUS "Bison compile flags: " ${BISON_CSParser_COMPILE_FLAGS})
    endif()
endif()


# Flex settings
find_package(FLEX 2.5.37)
if(FLEX_FOUND)
    FLEX_TARGET(CSScanner flex/CSScanner.l
            ${CMAKE_CURRENT_SOURCE_DIR}/generated/CSScanner.cc)
    if(FLEX_CSScanner_DEFINED)
        message(STATUS "Flex compile flags: " ${FLEX_CSScanner_COMPILE_FLAGS})
    endif()
endif()

# Add bison generated header dependency into flex scanner
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/generated)
ADD_FLEX_BISON_DEPENDENCY(CSScanner CSParser)

# Collect source files
set(SOURCE_FILES main.cpp)
set(SOURCE_FILES ${SOURCE_FILES} flex/CSScanner.hpp)
set(SOURCE_FILES ${SOURCE_FILES} Token.hpp Token.cpp)
set(SOURCE_FILES ${SOURCE_FILES} MetricsDriver.cpp MetricsDriver.hpp)

add_library(CSharpMetricsLib
        ${SOURCE_FILES}
        ${BISON_CSParser_OUTPUTS}
        ${FLEX_CSScanner_OUTPUTS})

add_executable(CSharpMetrics
        ${SOURCE_FILES}
        ${BISON_CSParser_OUTPUTS}
        ${FLEX_CSScanner_OUTPUTS})

# Check if directory for Flex/Bison generated files exists
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tmp)
    add_dependencies(CSharpMetrics CreateFlexBisonGeneratedDirectory)
    add_dependencies(CSharpMetricsLib CreateFlexBisonGeneratedDirectory)
endif()

