#pragma once
#include <iostream>
#include "SQLiteCpp/Database.h"
#include <string>
#include <vector>


#define SQL(...) #__VA_ARGS__

namespace DatabaseLibrary {
    struct Note {
        std::string note_identifier;
        std::string note;
    };

    /*
    TODO : funciton to merge two databases
    */
    class NotesDatabase {
        public:
        NotesDatabase(std::string filelocation);
        void InsertNote(std::string identifier, std::string note);
        std::string GetNote(std::string identifier);
        std::vector<Note> GetAllNotes();
        void DeleteNote(std::string identifier);

        

        private:
        SQLite::Database db;

    };
}