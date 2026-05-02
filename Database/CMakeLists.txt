add_library(DatabaseLibrary)
include(FetchContent)



add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

target_link_libraries(DatabaseLibrary SQLiteCpp)



target_sources(DatabaseLibrary
    PRIVATE
        Database.cpp
    PUBLIC 
        FILE_SET commandheaders
        TYPE HEADERS
        FILES
        Database.h 
)







