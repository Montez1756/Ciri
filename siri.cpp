#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

int main(){

    std::string command;
    std::vector<std::string> commandList;
    std::cout << "enter command" << std::endl;
    std::getline(std::cin, command);

    std::stringstream s(command);
    std::string word;
    while(s >> word){
        commandList.push_back(word);
    }
    std::vector<std::string> openCMDS = {"open","launch","start", "run"};
    for(int i=0; i<commandList.size(); i++){
        auto it = std::find(openCMDS.begin(), openCMDS.end(), commandList[i]);
        if(it != openCMDS.end()){

        }
    }
    return 0;
}