cmake_minimum_required(VERSION 3.10...3.14)

project(avm LANGUAGES CXX)



add_executable(avm src/Parser.cpp src/main.cpp src/AWM.cpp src/CustomException.cpp src/FOperand.cpp src/Lexer.cpp)

target_include_directories(avm PRIVATE inc/)

set_target_properties(avm PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    USE_FOLDERS ON)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
    set (PROJECTNAME_ARCHITECTURE "x64")
else ()
    set (PROJECTNAME_ARCHITECTURE "x86")
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT scop)
