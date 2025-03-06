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


// namespace fs = std::filesystem;


// Add similar functions for EA App, Uplay, GOG, etc...

int main() {
    std::ifstream file("path.json");

    nlohmann::json json = nlohmann::json::parse(file);
    for(const auto obj: json){
        std::string type = obj["type"];
        type = type.substr(0, type.length() - 1);
        for(const auto obj1: obj[type]){
            std::string os = "windows";
            #ifdef __linux__
                os = "linux";
            #endif
            #ifdef __APPLE__
                os = "macos";
            #endif
            nlohmann::json::array_t top = obj1[os]["toppath"];
            // for(const auto t: top){
            //     // if(fs::exists(t)){

            //     // }
            // }
            // std::cout << obj1["name"] << std::endl;
        }
    }
    return 0;
}
