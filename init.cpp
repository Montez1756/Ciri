#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <cstdlib>
#elif __APPLE__
#include <cstdlib>
#endif



std::vector<std::string> paths;
#ifdef _WIN32
paths = {""}
#endif
// Function to check if a path exists
bool pathExists(const std::string& path) {
    // return fs::exists(path);
    return true;
}

// Function to detect the Steam path
std::map<std::string, std::string> getGamePaths(){
    std::map<std::string, std::string> paths;
    std::string steam;
    std::string epicgames;
    #ifdef _WIN32
    std::string path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\";
    if (pathExists(path)) {
        steam = path;
    }
    path = "C:\\Program Files\\Epic Games\\";
    if (pathExists(path)) {
        epicgames = path;
    }
    #endif

    // Linux
    #ifdef __linux__
    const char* homeDir = std::getenv("HOME");
    std::string path = std::string(homeDir) + "/.steam/steam/steamapps/common/";
    if (pathExists(path)) {
        steam = path;
    }
    path = "~/.local/share/epicgames/";
    if (pathExists(path)) {
        epicgames = path;
    }
    #endif

    // macOS
    #ifdef __APPLE__
    const char* homeDir = std::getenv("HOME");
    std::string path = std::string(homeDir) + "/Library/Application Support/Steam/steamapps/common/";
    if (pathExists(path)) {
        steam = path;
    }
    std::string path = "~/Library/Application Support/Epic/";
    if (pathExists(path)) {
        epicgames = path;
    }
    #endif
    paths.emplace("steam", steam);
    paths.emplace("epicgames", epicgames);
    return paths;
}


// Add similar functions for EA App, Uplay, GOG, etc...

int main() {
    std::map<std::string, std::string> gamePaths = getGamePaths();
    if(!gamePaths.empty()){
        std::ofstream file("");
        if(file.is_open()){
        }
        else{
            std::cerr << "Failed to open xml file";
        }
    }
    return 0;
}
