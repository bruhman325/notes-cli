#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>


namespace CommandLibrary {    
    struct CommandInfo;
    struct UserInput {
        std::vector<std::string> args;
        std::vector<std::string> flags;
    };

    class CommandManager {
        public:
        /*
        When you register a command please ensure to put all the flags it uhh implements into description
        */
        void RegisterCommand(std::string name, std::string description, std::function<void(UserInput,CommandManager, std::shared_ptr<void>)> callback, std::shared_ptr<void> data);
        void RegisterDefaultBehavior(std::function<void(UserInput,CommandManager,std::shared_ptr<void>)>, std::shared_ptr<void>);
        /*
        If default behavior is registered invalid commands will be sent to the default behavior function
        */
        std::vector<CommandInfo> GetAllCommands();
        void HandleCommand(int argc, char** argv);

        private:

        std::map<std::string, CommandInfo> commands;
        UserInput ConvertInput(int argc, char** argv);
        std::shared_ptr<CommandInfo> defaultBehavior;
    };

    struct CommandInfo {
        std::string name;
        std::string usage;
        std::function<void(UserInput,CommandManager, std::shared_ptr<void>)> callback;
        std::shared_ptr<void> data;
    };

    bool inline VectorHasString(std::vector<std::string> vec, std::string str) {
        for (auto iterator = vec.begin(); iterator != vec.end(); ++iterator) {
            if (*iterator == str) return true;
        }
        return false;
    }
}