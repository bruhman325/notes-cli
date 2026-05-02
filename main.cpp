#include <iostream>
#include "Database.h"
#include "CommandManager.h"

#if defined(_WIN32) 
    #define DB_DIRECTORY "APPDATA"
#elif defined(__linux__)
    #define DB_DIRECTORY "HOME"
#endif

void WriteCommand(CommandLibrary::UserInput input, CommandLibrary::CommandManager manager, std::shared_ptr<void> data) {
    /*
    args[0] = note identiifer
    args[1...end] = note;
    */
   if (input.args.size() < 2) return;
   std::shared_ptr<DatabaseLibrary::NotesDatabase> db  = std::static_pointer_cast<DatabaseLibrary::NotesDatabase>(data);
   std::string note = input.args[1];
   for (int i = 2; i < input.args.size(); i++) {
    note += " " + input.args[i];
   }
   db->InsertNote(input.args[0],note);
}

void DeleteCommand(CommandLibrary::UserInput input, CommandLibrary::CommandManager manager, std::shared_ptr<void> data) {
    std::shared_ptr<DatabaseLibrary::NotesDatabase> db  = std::static_pointer_cast<DatabaseLibrary::NotesDatabase>(data);
    if (CommandLibrary::VectorHasString(input.flags,"--all")) {
        std::vector<DatabaseLibrary::Note> notes = db->GetAllNotes();
        for (auto i = notes.begin(); i != notes.end(); ++i) {
            db->DeleteNote(i->note_identifier);
        }
    }
    if (input.args.size() < 1) return;
    db->DeleteNote(input.args[0]);
}

void ReadCommand(CommandLibrary::UserInput input, CommandLibrary::CommandManager manager, std::shared_ptr<void> data) {
    /* 
    args[0] = note identifier;
    */
   std::shared_ptr<DatabaseLibrary::NotesDatabase> db  = std::static_pointer_cast<DatabaseLibrary::NotesDatabase>(data);
   
   if (CommandLibrary::VectorHasString(input.flags,"--all")) {
    std::vector<DatabaseLibrary::Note> notes = db->GetAllNotes();
    for (auto i = notes.begin(); i != notes.end(); ++i) {
        std::cout << i->note_identifier << " : " << i->note << std::endl;
    }
    return;
   }


   if (input.args.size() < 1) return;
   
   std::string note = db->GetNote(input.args[0]);
   std::cout << note << std::endl;
}

void HelpCommand(CommandLibrary::UserInput input, CommandLibrary::CommandManager manager, std::shared_ptr<void> data) {
    std::vector<CommandLibrary::CommandInfo> commands = manager.GetAllCommands();
    std::cout << "USAGE : " << std::endl;
    for (auto i = commands.begin(); i != commands.end(); i++) {
        std::cout << i->name << " " << i->usage << std::endl;
    }
}

void DefaultBehavior(CommandLibrary::UserInput input, CommandLibrary::CommandManager manager, std::shared_ptr<void> data) {
    switch (input.args.size())
    {
    case 0:
        HelpCommand(input,manager,data);
        break;
    case 1:
        ReadCommand(input,manager,data);
        break;
    default:
        WriteCommand(input,manager,data);
        break;
    }

}

bool EnsureDirectoryExists(std::string& final_directory) {
    char* dbStartDir = std::getenv(DB_DIRECTORY);
    if (dbStartDir == nullptr) return false;
    
    std::string dbDirectory = dbStartDir;
    dbDirectory += "/.local/man-notes";
    if(!std::filesystem::is_directory(dbDirectory)) {
        bool success = std::filesystem::create_directory(dbDirectory);
        if (!success) return false;
    }
    final_directory = dbDirectory;
    return true;  
}

int main(int argc, char* argv[]) {
    std::string dir = "";
    bool success = EnsureDirectoryExists(dir);
    if (!success) return -1;
    dir += "/database.db3";

    
    std::shared_ptr<DatabaseLibrary::NotesDatabase> notes  = std::make_shared<DatabaseLibrary::NotesDatabase>(dir);
    CommandLibrary::CommandManager manager = CommandLibrary::CommandManager();
    manager.RegisterDefaultBehavior(DefaultBehavior,notes);
    manager.RegisterCommand("write","note_identifier note_contents", WriteCommand, notes);
    manager.RegisterCommand("read", "note_identifier (--all)", ReadCommand, notes);
    manager.RegisterCommand("delete","note_identifier (--all)",DeleteCommand,notes);
    manager.HandleCommand(argc,argv);
    return 0;
}
