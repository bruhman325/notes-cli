#include "Database.h"
using namespace DatabaseLibrary;



NotesDatabase::NotesDatabase(std::string filelocation) : db(filelocation,SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE) {
    db.exec(SQL(
        CREATE TABLE IF NOT EXISTS notes (
            note_name TEXT PRIMARY KEY,
            note TEXT       
    )));
}

void NotesDatabase::InsertNote(std::string identifier, std::string note) {
    std::string statement = "INSERT INTO notes VALUES('" + identifier + "' , '" + note + "')";
    try {
        db.exec(statement);
    } catch (SQLite::Exception e) {
        if (e.getErrorCode() == 19) {
            std::string new_statement = "DELETE FROM notes WHERE note_name = '" + identifier + "'"; // might add an override bool
            db.exec(new_statement);
            InsertNote(identifier,note);
        }
    }
}

std::string NotesDatabase::GetNote(std::string identifier) {
    SQLite::Statement query(db,"SELECT note_name, note FROM notes WHERE note_name = ?");
    query.bind(1,identifier);
    bool success = query.executeStep();

    std::string note = success ? query.getColumn(1) : "No note found";

    return note;
}

std::vector<Note> NotesDatabase::GetAllNotes() {
    SQLite::Statement query(db,"SELECT * FROM notes");
    std::vector<Note> notes = {};
    while (query.executeStep()) {
        std::string identifier = query.getColumn(0);
        std::string noteContents = query.getColumn(1);

        Note note = {identifier, noteContents};
        notes.push_back(note);
    }
    return notes;
}

void NotesDatabase::DeleteNote(std::string noteIdentifier) {
    std::string statement = "DELETE FROM notes WHERE note_name = '" + noteIdentifier + "'";
    db.exec(statement);
}