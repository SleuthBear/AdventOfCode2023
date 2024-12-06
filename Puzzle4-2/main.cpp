#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <chrono>

// modified getPoints function from first puzzle.
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
                    score++;
                    val = 0;
                }
            }
        } else if (c == '|') {
            val = 0;
            winners = false;
        } else {
            if(winners and val != 0) {
                winningNums.insert(val);
                val = 0;
            } else if(winningNums.contains(val)) {
                score++;
                val = 0;
            } else {
                val = 0;
            }
        }
    }
    return score;

}

int numberOfCards(std::vector<std::string> *games, int gameNum) {
    // base case, return 0.
    if(gameNum >= games->size()) return 0;
    // inductive case, calculate number of points.
    int nCards = 1;
    for(int i = 1; i <= getPoints((*games)[gameNum]); i++) {
        // std::cout << gameNum + i << ' ';
        nCards += numberOfCards(games, gameNum + i);
    }
    return nCards;
}

int main()
{
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle4-2/input.txt");
    if (!myFile) {
        std::cerr << "Can't open input file!";
        return -1;
    }

    std::vector<std::string> games;
    if(myFile.is_open()) {
        std::string line;
        while(getline(myFile, line, '\n')) {
            games.push_back(line);
        }
    }
    auto start = std::chrono::steady_clock::now();
    int total = 0;
    for(int i = 0; i < games.size(); i++) {
        total += numberOfCards(&games, i);
    }
    std::cout << '\n' << total << '\n';
    auto stop = std::chrono::steady_clock::now();
    std::cout << duration_cast<std::chrono::milliseconds>(stop - start);
}
