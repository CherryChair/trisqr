cmake_minimum_required(VERSION 3.19)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexer main.cpp lexer.cpp lexer.h parser.cpp parser.h ErrorHandler.cpp ErrorHandler.h Token.cpp Token.h)

add_subdirectory(googletest)
