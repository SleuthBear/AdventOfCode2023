#include <fstream>
#include <iostream>
using namespace std;
int RMAX = 12;
int BMAX = 14;
int GMAX = 13;

bool gamePossible(string game) {
    int val = 0;
    game = game.substr(game.find_first_of(':'), game.length());
    for(char c: game) {
        if(c == 'r') {
            if (val > RMAX and val != 0) {
                cout << val << " fail on red \n";
                return false;
            }
            val = 0;
        } else if(c == 'g') {
            if (val > GMAX and val != 0) {
                cout << val << " fail on green \n";
                return false;
            }
            val = 0;
        } else if(c == 'b' and val != 0) {
            if (val > BMAX) {
                cout << val << " fail on blue \n";
                return false;
            }
            val = 0;
        } else if('0' <= c and c <= '9') {
            val = val*10 + c-'0';
        }
    }
    return true;
}

int minPossiblePower(string game) {
    int val = 0;
    int minRed = 0, minGreen = 0, minBlue = 0;
    game = game.substr(game.find_first_of(':'), game.length());
    for(char c: game) {
        if(c == 'r') {
            if (val > minRed and val != 0) {
                minRed = val;
            }
            val = 0;
        } else if(c == 'g') {
            if (val > minGreen and val != 0) {
                minGreen = val;
            }
            val = 0;
        } else if(c == 'b') {
            if (val > minBlue and val != 0) {
                minBlue = val;
            }
            val = 0;
        } else if('0' <= c and c <= '9') {
            val = val*10 + c-'0';
        }
    }
    return minRed*minBlue*minGreen;
}

int main() {
    ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle2/input.txt");
    int sum = 0;
    int possibleSum = 0;
    if (!myFile) cerr << "Can't open input file!";
    if(myFile.is_open()) {
        string line;
        while(getline(myFile, line, '\n')) {
            cout << line << '\n';
            possibleSum += minPossiblePower(line);
            if(gamePossible(line)){
                cout << "possible" << '\n';
                sum += stoi(line.substr(5, line.find_first_of(':')));
            }
        }
    }
    cout << sum << '\n';
    cout << possibleSum;
    return sum;
}
