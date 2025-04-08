cmake_minimum_required(VERSION 3.10)
project(MyAntlrVhdl)

set(CMAKE_CXX_STANDARD 17)

# ANTLR4 runtime source
add_subdirectory(antlr4/runtime/Cpp runtime)

# Include directories
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/antlr4-runtime/runtime/Cpp/runtime/src
)

# Your parser files and main
add_executable(MyParser
        main.cpp
        generated/vhdlLexer.cpp
        generated/vhdlParser.cpp
        generated/vhdlBaseListener.cpp
        generated/vhdlListener.cpp
)

# Link to ANTLR runtime
target_link_libraries(MyParser antlr4_static)
