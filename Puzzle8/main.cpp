#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle8/input.txt");
    std::string line;
    std::map<std::string, std::vector<std::string>> nodeMap;
    getline(myFile, line, '\n');
    std::string turns = line;
    getline(myFile, line, '\n');
    std::cout << "line" << line << std::endl;
    while(getline(myFile, line, '\n')) {
        nodeMap[line.substr(0, 3)] = {line.substr(7,3), line.substr(12,3)};
    }
    // for(auto const& [key, values]: nodeMap) {
    //     std::cout << "key->" << key << " values->" << values[0] << "-" << values[1] << std::endl;
    // }
    int counter = 0;
    std::string current = "AAA";
    bool notFound = true;
    while(notFound) {
        for(char c: turns) {
            if(current == "ZZZ") {
                notFound = false;
                break;
            }
            counter++;
            current = c == 'L' ? nodeMap[current][0] : nodeMap[current][1];
        }
    }

    std::cout << counter << ' ' << current << std::endl;
}
