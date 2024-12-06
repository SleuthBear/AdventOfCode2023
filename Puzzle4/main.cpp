#include <fstream>
#include <iostream>
#include <set>
#include <vector>

int getPoints(std::string line)
{
    bool winners = true;
    int val = 0;
    int score = 0;
    int start = line.find_first_of(':')+2;
    line = line.substr(start, line.size()-start);
    std::set<int> winningNums;
    int i = 0;
    for(char c: line) {
        i++;
        if('0' <= c and c <= '9') {
            val = val*10 + c - '0';
            if(i == line.size()) { // end of line
                if(winningNums.contains(val)) {
                    std::cout << "contains " << val << '\n';
                    score = score == 0 ? 1 : score*2;
                    std::cout << "score " << score << '\n';
                    val = 0;
                }
            }
        } else if (c == '|') {
            val = 0;
            winners = false;
        } else {
            if(winners and val != 0) {
                std::cout << "inserting winner " << val << '\n';
                winningNums.insert(val);
                val = 0;
            } else if(winningNums.contains(val)) {
                std::cout << "contains " << val << '\n';
                score = score == 0 ? 1 : score*2;
                std::cout << "score " << score << '\n';
                val = 0;
            } else {
                val = 0;
            }
        }
    }
    return score;

}





int main()
{
    // create our input vector
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle4/input.txt");
    if (!myFile) {
        std::cerr << "Can't open input file!";
        return -1;
    }

    int pointSum = 0;
    if(myFile.is_open()) {
        std::string line;
        while(getline(myFile, line, '\n')) {
            pointSum += getPoints(line);
        }
    }
    std::cout << pointSum << '\n';
    return 0;
}
