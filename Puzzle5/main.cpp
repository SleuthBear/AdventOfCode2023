#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

// get the number we are trying to pass through,
// go to the first map, for each line, do a bounds check if it fits,
// if it fits, return a new number and go through the next map
// if it doesn't return the number itself.

std::vector<unsigned long long> extractNumbers(std::string line) {
    std::vector<unsigned long long> numbers;
    unsigned long long val = 0;
    bool readingNum = false;
    for(int i = 0; i < line.length(); i++) {
        if('0' <= line[i] and line[i] <= '9') {
            val = val*10 + line[i]-'0';
            readingNum = true;
        } else if (readingNum == true) {
            readingNum = false;
            std::cout << val << '\n';
            numbers.push_back(val);
            val = 0;
        }
    }
    if(readingNum) numbers.push_back(val);
    return numbers;
}

unsigned long long mapLine(std::string line, unsigned long long toMap) {
    unsigned long long destination = -1;
    unsigned long long source = -1;
    unsigned long long range = -1;
    unsigned long long val = 0;
    for(int i = 0; i < line.length(); i++) {
        if(line[i] <= '9' and '0' <= line[i]) {
            val = val*10 + line[i]-'0';
            if(i == line.length()-1) {
                range = val;
            }
        } else {
            if(destination != -1 and source != -1) range = val;
            else if(destination != -1) source = val;
            else destination = val;
            val = 0;
        }
    }
    if(source <= toMap and toMap <= source + range) {
        return destination + toMap-source;
    }
    return toMap;
}

int main()
{
    // create our input vector
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle5/testInput.txt");
    if (!myFile) {
        std::cerr << "Can't open input file!";
        return -1;
    }

    std::vector<std::string> input;
    if(myFile.is_open()) {
        std::string line;
        while(getline(myFile, line, '\n')) {
            input.push_back(line);
        }
    }
    std::vector<unsigned long long> toMaps = extractNumbers(input[0]);
    std::cout << "toMaps: " << toMaps[0] << '\n';
    unsigned long long minLocation = 99999999999;
    std::cout << minLocation << '\n';
    unsigned long long newMap;
    for(unsigned long long toMap: toMaps) {
        std::cout << toMap;
        int i = 0;
        bool hasFlipped = false;
        while(i<input.size()) {
            if(input[i][0] > '9' or input[i][0] < '0') {
                i++;
                hasFlipped = false;
            } else if(input[i][0] >= '0' and input[i][0] <= '9' and hasFlipped == false) {
                // std::cout << input[i] << '\n';
                newMap = mapLine(input[i], toMap);
                if(newMap != toMap) {
                    hasFlipped = true;
                    // std::cout << toMap << " -> " << newMap << '\n';
                    toMap = newMap;
                    std::cout << "->" << toMap;
                }
                i++;
            } else {
                i++;
            }

        }
        std::cout << "->" << toMap << '\n';
        if(toMap < minLocation) minLocation = toMap;
    }
    std::cout << std::setprecision (15) << minLocation << std::endl;
    return 0;
}
