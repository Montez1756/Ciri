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

int main() {
    std::ifstream file("data/path.json");

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

            std::vector<nlohmann::json::string_t> top = obj1[os]["toppath"];
            std::vector<nlohmann::json::string_t> exes = obj1[os]["exe"];
            for(const auto t: top){
                std::cout << t << std::endl;
                // if(fs::exists(t)){

                //     for(const auto exe: exes){
                //         if(fs::exists(t + exe)){
                //             std::cout << t + exe  << std::endl;
                //         }
                //     }
                // }
            }
        }
    }
    return 0;
}
