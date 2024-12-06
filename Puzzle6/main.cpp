#include <fstream>
#include <iostream>
#include <vector>

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
            numbers.push_back(val);
            val = 0;
        }
    }
    if(readingNum) numbers.push_back(val);
    return numbers;
}

unsigned long long numWins(unsigned long long time, unsigned long long  distance) {
    long double timeFloat = time;
    long double distanceFloat = distance;
    long double lower = (timeFloat/2.0 -  0.5*std::sqrt(timeFloat*timeFloat-4.0*distanceFloat))+1.0;
    long double upper = (timeFloat/2.0 +  0.5*std::sqrt(timeFloat*timeFloat-4.0*distanceFloat));
    std::cout << upper << " " << lower << '\n';
    if (std::floorf(lower) == lower) {
        return static_cast<unsigned long long >(upper)-static_cast<unsigned long long >(lower);
    }
    return static_cast<unsigned long long >(upper)-static_cast<unsigned long long >(lower)+1;
}

int main() {
    // extract all times
    // extract all distances
    // for each time and distance calculate the range following this formula.
    // multiply together
    // profit
 // create our input vector
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle6/input.txt");
    if (!myFile) {
        std::cerr << "Can't open input file!";
        return -1;
    }
    int product = 1;
    std::string line;
    getline(myFile, line, '\n');
    std::vector<unsigned long long> times = extractNumbers(line);
    getline(myFile, line, '\n');
    std::vector<unsigned long long> distances = extractNumbers(line);
    for(int i = 0; i < times.size(); i++) {
        std::cout << numWins(times[i], distances[i]) << '\n';
        product = product*numWins(times[i], distances[i]);
    }
    std::cout << product;

}
