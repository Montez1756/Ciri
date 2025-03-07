#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include "ciriConsole.h"

// Helper: Convert string to lowercase
std::string toLower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Helper: Extract file name from path
std::string getFileName(const std::string &path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}


// Initialize command map
void ciriConsole::initializeCommands() {
    commandMap["open"] = &ciriConsole::openProgram;
    commandMap["launch"] = &ciriConsole::openProgram;
    commandMap["start"] = &ciriConsole::openProgram;
    commandMap["run"] = &ciriConsole::openProgram;

    commandMap["shutdown"] = &ciriConsole::shutdownSystem;
    commandMap["restart"] = &ciriConsole::restartSystem;
    commandMap["signout"] = &ciriConsole::signOutUser;

    
}

// Main command handler
int ciriConsole::runCommand(const std::string &input) {
    // Initialize commands on the first call
    static bool initialized = false;
    if (!initialized) {
        initializeCommands();
        initialized = true;
    }

    // Tokenize the input
    std::stringstream ss(input);
    std::vector<std::string> commandList;
    std::string word;
    while (ss >> word) {
        commandList.push_back(toLower(word)); // Store lowercase version for matching
    }

    if (commandList.empty()) return 0; // No command entered

    // Search for the command in the map
    auto it = commandMap.find(commandList[0]);
    if (it != commandMap.end()) {
        (this->*(it->second))(commandList); // Execute associated function
    } else {
        std::cerr << "Unknown command: " << commandList[0] << std::endl;
    }
    return 0;
}

// Command: Open program from paths.txt
void ciriConsole::openProgram(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        std::cerr << "Usage: open <program>" << std::endl;
        return;
    }

    std::string program = args[1];
    std::ifstream file("data/paths.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open paths.txt\n";
        return;
    }

    std::string path;
    while (std::getline(file, path)) {
        if (toLower(getFileName(path)).find(program) != std::string::npos) {
            std::cout << "Launching: " << path << std::endl;
            system(path.c_str());
            return;
        }
    }

    std::cerr << "Program not found: " << program << std::endl;
}

// Command: Shutdown system
void ciriConsole::shutdownSystem(const std::vector<std::string> &args) {
    #if defined(_WIN32) || defined(_WIN64)
        std::system("shutdown /s /t 0");
    #elif defined(__linux__) || defined(__unix__)
        std::system("shutdown now");
    #elif defined(__APPLE__)
        std::system("sudo shutdown -h now");
    #endif
}

// Command: Restart system
void ciriConsole::restartSystem(const std::vector<std::string> &args) {
    #if defined(_WIN32) || defined(_WIN64)
        std::system("shutdown /r /t 0");
    #elif defined(__linux__) || defined(__unix__)
        std::system("reboot");
    #elif defined(__APPLE__)
        std::system("sudo shutdown -r now");
    #endif
}

// Command: Sign out user
void ciriConsole::signOutUser(const std::vector<std::string> &args) {
    #if defined(_WIN32) || defined(_WIN64)
        std::system("shutdown /l");
    #elif defined(__linux__) || defined(__unix__)
        std::system("pkill -KILL -u $USER");
    #elif defined(__APPLE__)
        std::system("osascript -e 'tell application \"System Events\" to log out'");
    #endif
}
