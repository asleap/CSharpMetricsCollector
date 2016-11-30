cmake_minimum_required(VERSION 3.6)
project(CSharpMetrics)

set(SOURCE_FILES main.cpp)
set(SOURCE_FILES ${SOURCE_FILES} Token.hpp Token.cpp)
set(SOURCE_FILES ${SOURCE_FILES} Lexer.hpp Lexer.cpp)

add_executable(Lexer ${SOURCE_FILES})