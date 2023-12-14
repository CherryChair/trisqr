cmake_minimum_required(VERSION 3.19)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexer main.cpp lexer.cpp lexer.h ErrorHandler.cpp ErrorHandler.h Token.cpp Token.h Parser.cpp Parser.h Program/Program.cpp Program/Program.h Program/Visitator.cpp Program/Visitator.h position.h lexer_error_types.h)

add_subdirectory(googletest)
