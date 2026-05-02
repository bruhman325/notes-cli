
cmake_minimum_required(VERSION 3.12)

add_library(CommandLibrary)

target_sources(CommandLibrary
    PRIVATE
        CommandManager.cpp
    PUBLIC 
        FILE_SET dataheaders
        TYPE HEADERS
        FILES
        CommandManager.h 

        


)

