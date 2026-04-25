cmake_minimum_required(VERSION 3.29)
project(StoneMath)

set(CMAKE_CXX_STANDARD 20)

add_executable(StoneMath main.cpp
        include/Lexer.h
        src/Lexer.cpp
        include/TokenType.h
        include/Parser.h
        src/Parser.cpp
        include/Evaluator.h
        include/StoneMath.h
        src/Evaluator.cpp
        src/StoneMath.cpp
)
include_directories(include)