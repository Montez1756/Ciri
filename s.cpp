#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <map>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <cstdlib>
#elif __APPLE__
#include <cstdlib>
#endif

// namespace fs = std::filesystem;

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

// Function to detect the Epic Games Launcher path
std::string getEpicGamesPath() {
    // Windows
    #ifdef _WIN32
    std::string path = "C:\\Program Files\\Epic Games\\";
    if (pathExists(path)) {
        return path;
    }
    
    #endif

    // Linux (hypothetical location)
    #ifdef __linux__
    std::string path = "~/.local/share/epicgames/";
    if (pathExists(path)) {
        return path;
    }
    #endif

    // macOS
    #ifdef __APPLE__
    std::string path = "~/Library/Application Support/Epic/";
    if (pathExists(path)) {
        return path;
    }
    #endif

    return "";
}

// Add similar functions for EA App, Uplay, GOG, etc...

int main() {
    // Detect Steam
    std::string steamPath = getSteamPath();
    if (!steamPath.empty()) {
        std::cout << "Steam games installed at: " << steamPath << std::endl;
    } else {
        std::cout << "Steam not found." << std::endl;
    }

    // Detect Epic Games
    std::string epicPath = getEpicGamesPath();
    if (!epicPath.empty()) {
        std::cout << "Epic Games installed at: " << epicPath << std::endl;
    } else {
        std::cout << "Epic Games not found." << std::endl;
    }

    // Detect other launchers similarly...
    // You can add checks for EA App, Uplay, GOG, Battle.net, etc.

    return 0;
}
