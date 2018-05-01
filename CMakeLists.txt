cmake_minimum_required(VERSION 3.10)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 11)
include_directories(inc)

add_executable(Abstract_VM src/main.cpp inc/IOperand.hpp inc/Operand.hpp src/CustomException.cpp inc/CustomException.hpp src/FOperand.cpp inc/FOperand.hpp)