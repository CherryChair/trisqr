cmake_minimum_required(VERSION 3.19)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexer main.cpp lexer.cpp lexer.h ErrorHandler.cpp ErrorHandler.h Token.cpp Token.h Parser.cpp Parser.h Program/Program.cpp Program/Program.h Program/Visitor.cpp Program/Visitor.h position.h lexer_error_types.h Program/VisitorTree.cpp Program/VisitorTree.h Program/VisitorSemantic.cpp Program/VisitorSemantic.h Program/VisitorInterpreter.cpp Program/VisitorInterpreter.h)

#add_subdirectory(googletest)
