cmake_minimum_required(VERSION 3.19)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.0)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

add_executable(trisqr main.cpp Lexer/lexer.cpp Lexer/lexer.h ErrorHandler/ErrorHandler.cpp ErrorHandler/ErrorHandler.h Lexer/Token.cpp Lexer/Token.h Parser/Parser.cpp Parser/Parser.h Program/Program.cpp Program/Program.h Visitors/Visitor.cpp Visitors/Visitor.h Lexer/position.h Lexer/lexer_error_types.h Visitors/VisitorTree.cpp Visitors/VisitorTree.h Visitors/VisitorSemantic.cpp Visitors/VisitorSemantic.h  Visitors/VisitorInterpreter.cpp Visitors/VisitorInterpreter.h)

add_subdirectory(googletest)
target_link_libraries(trisqr PRIVATE PkgConfig::CAIROMM PkgConfig::GTK3)