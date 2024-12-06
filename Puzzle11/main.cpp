#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int STEP_CONSTANT = 1000000;

struct galaxy {
    int x;
    int y;
    galaxy(int inputX, int inputY)
        : x(inputX),
        y(inputY)
    {}
};

bool isEmptyRow(std::string line) {
    for(char c: line) {
        if(c == '#') return false;
    }
    return true;
}

bool isEmptyColumn(std::vector<std::string> &universe, int i) {
    for(std::string row: universe) {
        if(row[i] == '#') return false;
    }
    return true;
}

void insertColumn(std::vector<std::string> &universe, int i) {
    for(int j = 0; j < universe.size(); j++) {
        universe[j].replace(i, 1, "*");
    }
}


long long stepTo(std::vector<std::string> &universe, galaxy g1, galaxy g2) {
    long long steps = 0;
    int xStep = (g2.x-g1.x)/std::abs(g2.x-g1.x);
    int yStep = (g2.y-g1.y)/std::abs(g2.y-g1.y);
    for(int x = g1.x; x!=g2.x; x+=xStep) {
        if(universe[0][x] == '*') {
            steps += STEP_CONSTANT;
        } else {
            steps += 1;
        }
    }
    for(int y = g1.y; y!=g2.y; y+=yStep) {
        if(universe[y][0] == '*') {
            steps += STEP_CONSTANT;
        } else {
            steps += 1;
        }
    }
    return steps;
}

void expand (std::vector<std::string> &universe) {
    //add rows
    for(int i = 0; i<universe.size(); i++) {
        if(isEmptyRow(universe[i])) {
            universe[i] = std::string(universe[i].length(), '*');
        }
    }
    for(int i = 0; i < universe[0].length(); i++) {
        if(isEmptyColumn(universe, i)) {
            insertColumn(universe, i);
        }
    }
}


int main()
{
    std::ifstream file("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle11/input.txt");
    std::string line;
    std::vector<std::string> universe;
    while(getline(file, line, '\n')) {
        universe.push_back(line);
    }
    for(std::string row: universe) {
        std::cout << row << '\n';
    }
    expand(universe);
    std::cout << '\n';
    for(std::string row: universe) {
        std::cout << row << '\n';
    }
    std::vector<galaxy> galaxies;
    for(int i = 0; i < universe.size(); i++) {
        for(int j = 0; j < universe[0].length(); j++) {
            if(universe[i][j] == '#') {
                galaxies.emplace_back(j, i);
            }
        }
    }
    unsigned long long sum = 0;
    for(int i = 0; i < galaxies.size(); i++) {
        for(int j = i+1; j < galaxies.size(); j++) {
           sum += stepTo(universe, galaxies[i], galaxies[j]);
        }
    }
    std::cout << sum << std::endl;
}
