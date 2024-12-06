#include <iostream>
#include <fstream>
#include <map>

struct node {
    std::string val;
    std::string leftString;
    std::string rightString;
    node *left;
    node *right;
    bool isEnd;
};

int main() {
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle8-2/input.txt");
    std::string line;
    std::map<std::string, node> nodeMap;
    getline(myFile, line, '\n');
    std::string turns = line;
    getline(myFile, line, '\n');
    std::vector<node> movers;

    while(getline(myFile, line, '\n')) {
        node thisNode = node();
        thisNode.val = line.substr(0,3);
        thisNode.leftString = line.substr(7,3);
        thisNode.rightString = line.substr(12,3);
        thisNode.isEnd = line[2] == 'Z';
        nodeMap[line.substr(0, 3)] = thisNode;

    }

    for(auto const &[key, value] : nodeMap) {
        nodeMap[key].left = &nodeMap[value.leftString];
        nodeMap[key].right = &nodeMap[value.rightString];
        if(value.val[2] == 'A') movers.push_back(value);
    }

    for(node mover: movers) {
        std::cout << mover.val << std::endl;
    }

    int counter = 0;
    bool notFound = true;
    while(notFound) {
        // std::cout << counter << std::endl;
        for(char c: turns) {
            for(node &mover : movers) {
                mover = c == 'L' ? mover = *mover.left : *mover.right;
            }
            counter++;
            notFound = false;
            for(node mover : movers) {
                if(mover.val[2] != 'Z') {
                    notFound = true;
                    break;
                }
            }
            if(!notFound) break;
        }
    }
    for(node mover: movers) {
        std::cout << mover.val << std::endl;
    }
    std::cout << counter << std::endl;
}
