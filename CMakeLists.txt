cmake_minimum_required(VERSION 3.10...3.14)

project(avm LANGUAGES CXX)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

option(BUILD_WITH_UNIT_TESTS "Build with unit test" OFF)


add_executable(avm 
                src/Parser.cpp
                src/main.cpp
                src/AWM.cpp
                src/CustomException.cpp
                src/FOperand.cpp
                src/Lexer.cpp
                )

target_include_directories(avm PUBLIC inc/)

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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT avm)

if (BUILD_WITH_UNIT_TESTS)
    include(cmake/googletest.cmake)
    fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
        )
    enable_testing()
    add_subdirectory(tests)
endif()