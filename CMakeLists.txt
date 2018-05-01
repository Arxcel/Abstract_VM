cmake_minimum_required(VERSION 3.9)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 11)
include_directories(inc)

add_executable(Abstract_VM src/main.cpp src/FOperand.cpp inc/FOperand.hpp inc/IOperand.hpp inc/Operand.hpp src/CustomException.cpp inc/CustomException.hpp src/Lexer.cpp inc/Lexer.hpp src/Parser.cpp inc/Parser.hpp src/AWM.cpp inc/AWM.hpp)