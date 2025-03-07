#ifndef CIRI_CONSOLE_H
#define CIRI_CONSOLE_H

#include <string>
#include <vector>
#include <unordered_map>

class ciriConsole {
    public:
        int runCommand(const std::string &command);
    
    private:
        // Function mapping for commands
        using CommandFunc = void (ciriConsole::*)(const std::vector<std::string>&);
        std::unordered_map<std::string, CommandFunc> commandMap;
    
        // Command functions
        void openProgram(const std::vector<std::string> &args);
        void shutdownSystem(const std::vector<std::string> &args);
        void restartSystem(const std::vector<std::string> &args);
        void signOutUser(const std::vector<std::string> &args);
    
        // Helper: Initialize command map
        void initializeCommands();
    };

#endif