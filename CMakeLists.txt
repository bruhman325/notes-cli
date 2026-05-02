cmake_minimum_required(VERSION 3.12)

project(NotesProject)

set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS OFF)     

add_executable(notes)

target_sources(notes PRIVATE main.cpp )

add_subdirectory(Commands)
add_subdirectory(Database)

target_link_libraries(notes PRIVATE CommandLibrary DatabaseLibrary)


install(TARGETS notes DESTINATION bin)

