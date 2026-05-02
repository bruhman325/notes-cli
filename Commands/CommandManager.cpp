
#include "CommandManager.h"
using namespace CommandLibrary;


std::vector<CommandInfo> CommandManager::GetAllCommands() {
    std::vector<CommandInfo> allCommands;
    for (auto iterator = commands.begin(); iterator != commands.end(); ++iterator) {
        allCommands.push_back(iterator->second);
    }
    return allCommands;
}

void CommandManager::RegisterCommand(std::string name, std::string description, std::function<void(UserInput,CommandManager, std::shared_ptr<void>)> callback, std::shared_ptr<void> data) {
    CommandInfo info = {};
    info.callback = callback;
    info.data = data;
    info.usage = description;
    info.name = name;
    commands[name] = info; // maybe do some checkign to see if the command already exists idk
}

void CommandManager::RegisterDefaultBehavior(std::function<void(UserInput,CommandManager, std::shared_ptr<void>)> callback, std::shared_ptr<void> data) {
    defaultBehavior = std::make_shared<CommandInfo>();
    defaultBehavior->callback = callback;
    defaultBehavior->data = data;
}

UserInput CommandManager::ConvertInput(int argc, char** argv) {
    std::vector<std::string> args;
    std::vector<std::string> flags;
    
    for (int i = 1; i < argc; i++) { // index starts at two to skip the program name 
        std::string str = std::string(argv[i]);
        bool flag = str.length() > 1 && (str.substr(0,2) == "--");
        if (flag) flags.push_back(str);
        else args.push_back(str);
    }        

    UserInput input = {args,flags};
    return input;
}

void CommandManager::HandleCommand(int argc, char** argv) {
    UserInput input = ConvertInput(argc, argv);
    if (input.args.size() < 1) {
        if (defaultBehavior != nullptr) {
            defaultBehavior->callback(input,*this,defaultBehavior->data);
        }
        return;
    }

    std::string commandName = input.args.front();
    
    CommandInfo info;
    
    try { // there is probably a better way to do this
    info = commands.at(commandName); 
    } catch (std::out_of_range) {
        if (defaultBehavior != nullptr) { // call default behavior if it isnt a valid command name
            defaultBehavior->callback(input,*this,defaultBehavior->data);
            return;
        }
        std::cout << "command not found";
        return;
    }

    input.args.erase(input.args.begin()); // dont want the command name to be in the argument list
    info.callback(input,*this,info.data);
}

