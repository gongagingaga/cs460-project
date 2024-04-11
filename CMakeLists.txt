cmake_minimum_required(VERSION 3.26)
project(TokenizerProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(TokenizerProject main.cpp
        Token.cpp
        Token.hpp
        Tokenizer.cpp
        Tokenizer.hpp
        Parser.cpp
        Parser.hpp
        SymbolTable.cpp
        SymbolTable.hpp
        SymbolTableNode.cpp
        SymbolTableNode.hpp
        cst.cpp
        cst.hpp)