cmake_minimum_required(VERSION 3.16)
project(Project2_Trifecta_Finder)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2_Trifecta_Finder main.cpp
        Trie.h
        HashTable.h
        SongLoader.h)