cmake_minimum_required(VERSION 3.15)
project(SysY-Compiler)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

add_executable(SysY-Compiler main.cpp  Lexer/Lexer.cpp Lexer/Lexer.h Parser/Parser.cpp Parser/Parser.h Lexer/LexType.h)