#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int findNumStart(int j, string line) {
    while(j > 0 and line[j-1] <= '9' and line[j-1] >= '0') {
        j--;
    }
    return j;
}

int getNum(string line, int j) {
    int val = 0;
    while(line[j] <= '9' and line[j] >= '0') {
        val = val*10 + line[j] - '0';
        j++;
    }
    cout << j << ' ' << val << '\n';
    return val;
}
// I reversed them fuuuuuck
int adjacentSymbol(vector<string> inputVector, int i, int j) {
    // left
    int product = 0;
    int iStart = -1;
    int jStart = -1;
    int adjs = 0;
    if(j > 0  and (inputVector[i][j-1] <= '9' and inputVector[i][j-1] >= '0')) {
        int start = findNumStart(j-1, inputVector[i]);
        if(iStart != i or jStart != start) { // haven't seen this number before
            iStart = i;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i], start);
            if(adjs == 1) product = product*getNum(inputVector[i], start);
            adjs++;
        }
    }
    // right
    if(j < inputVector[0].length()-1 and (inputVector[i][j+1] <= '9' and inputVector[i][j+1] >= '0')) {
        int start = findNumStart(j+1, inputVector[i]);
        if(iStart != i or jStart != start) { // haven't seen this number before
            iStart = i;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i], start);
            if(adjs == 1) product = product*getNum(inputVector[i], start);
            adjs++;
        }
    }
    // left up
    if(j > 0 and i > 0 and (inputVector[i-1][j-1] <= '9' and inputVector[i-1][j-1] >= '0')) {
        int start = findNumStart(j-1, inputVector[i-1]);
        if(iStart != i-1 or jStart != start) { // haven't seen this number before
            iStart = i-1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i-1], start);
            if(adjs == 1) product = product*getNum(inputVector[i-1], start);
            adjs++;
        }
    }
    // up
    if(i > 0 and (inputVector[i-1][j] <= '9' and inputVector[i-1][j] >= '0')) {
        int start = findNumStart(j, inputVector[i-1]);
        if(iStart != i-1 or jStart != start) { // haven't seen this number before
            iStart = i-1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i-1], start);
            if(adjs == 1) product = product*getNum(inputVector[i-1], start);
            adjs++;
        }
    }
    // right up
    if(j < inputVector[0].length()-1 and i > 0 and (inputVector[i-1][j+1] <= '9' and inputVector[i-1][j+1] >= '0')) {
        int start = findNumStart(j+1, inputVector[i-1]);
        if(iStart != i-1 or jStart != start) { // haven't seen this number before
            iStart = i-1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i-1], start);
            if(adjs == 1) product = product*getNum(inputVector[i-1], start);
            adjs++;
        }
    }
    // left down
    if(j > 0 and i < inputVector.size()-1 and (inputVector[i+1][j-1] <= '9' and inputVector[i+1][j-1] >= '0')) {
        int start = findNumStart(j-1, inputVector[i+1]);
        if(iStart != i+1 or jStart != start) { // haven't seen this number before
            iStart = i+1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i+1], start);
            if(adjs == 1) product = product*getNum(inputVector[i+1], start);
            adjs++;
        }
    }
    // down
    if(i < inputVector.size()-1 and (inputVector[i+1][j] <= '9' and inputVector[i+1][j] >= '0')) {
        int start = findNumStart(j, inputVector[i+1]);
        if(iStart != i+1 or jStart != start) { // haven't seen this number before
            iStart = i+1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i+1], start);
            if(adjs == 1) product = product*getNum(inputVector[i+1], start);
            adjs++;
        }
    }
    // right down
    if(j < inputVector[0].length()-1 and i < inputVector.size()-1 and (inputVector[i+1][j+1] <= '9' and inputVector[i+1][j+1] >= '0')) {
        int start = findNumStart(j+1, inputVector[i+1]);
        if(iStart != i+1 or jStart != start) { // haven't seen this number before
            iStart = i+1;
            jStart = start;
            if(adjs >= 2) return 0; // more than 2 adjacent
            if(adjs == 0) product = getNum(inputVector[i+1], start);
            if(adjs == 1) product = product*getNum(inputVector[i+1], start);
            adjs++;
        }
    }
    cout << "adjs = " << adjs << " product = " << product << '\n';
    if(adjs == 2) return product;
    return 0;
}

int main()
{
    // create our input vector
    ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle3-2/input.txt");
    if (!myFile) cerr << "Can't open input file!";
    vector<string> inputVector;
    if(myFile.is_open()) {
        string line;
        while(getline(myFile, line, '\n')) {
            inputVector.push_back(line);
        }
    }
    // iterate through each line to find a number, at each digit check if it is next to a symbol.
    // if it is, then isPart = true. once we reach the end of the number, if isPart, add to the sum.
    int sum = 0;
    for(int j = 0; j < inputVector.size(); j++) {
        for(int i = 0; i < inputVector.at(0).length(); i++) {
            if(inputVector[j][i] == '*') {
                cout << j << ' ' << i << '\n';
                sum += adjacentSymbol(inputVector, j, i);
            }
        }
    }
    cout << sum;
    return sum;
}
