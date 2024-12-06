#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// I reversed them fuuuuuck
bool adjacentSymbol(vector<string> inputVector, int i, int j) {
    // left
    if(j > 0 and (inputVector[i][j-1] != '.' and inputVector[i][j-1] != '\n') and (inputVector[i][j-1] > '9' or inputVector[i][j-1] < '0')) {
        return true;
    }
    // left up
    if(j > 0 and i > 0 and (inputVector[i-1][j-1] != '.' and inputVector[i-1][j-1] != '\n')  and (inputVector[i-1][j-1] > '9' or inputVector[i-1][j-1] < '0')) {
        return true;
    }
    // left down
    if(j > 0 and i < inputVector.size()-1 and (inputVector[i+1][j-1] != '.' and inputVector[i+1][j-1] != '\n')  and (inputVector[i+1][j-1] > '9' or inputVector[i+1][j-1] < '0')) {
        return true;
    }
    // right
    if(j < inputVector[0].length()-1 and (inputVector[i][j+1] != '.' and inputVector[i][j+1] != '\n')  and (inputVector[i][j+1] > '9' or inputVector[i][j+1] < '0')) {
        return true;
    }
    // right up
    if(j < inputVector[0].length()-1 and i > 0 and (inputVector[i-1][j+1] != '.' and inputVector[i-1][j+1] != '\n')  and (inputVector[i-1][j+1] > '9' or inputVector[i-1][j+1] < '0')) {
        return true;
    }
    // right down
    if(j < inputVector[0].length()-1 and i < inputVector.size()-1 and (inputVector[i+1][j+1] != '.' and inputVector[i+1][j+1] != '\n')  and (inputVector[i][j+1] > '9' or inputVector[i][j+1] < '0')) {
        return true;
    }
    // up
    if(i > 0 and (inputVector[i-1][j] != '.' and inputVector[i-1][j] != '\n')  and (inputVector[i-1][j] > '9' or inputVector[i-1][j] < '0')) {
        return true;
    }
    // down
    if(i < inputVector.size()-1 and (inputVector[i+1][j] != '.' and inputVector[i+1][j] != '\n')  and (inputVector[i+1][j] > '9' or inputVector[i+1][j] < '0')) {
        return true;
    }
    return false;
}

int main()
{
    // create our input vector
    ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle3/input.txt");
    if (!myFile) cerr << "Can't open input file!";
    vector<string> inputVector;
    if(myFile.is_open()) {
        string line;
        while(getline(myFile, line, '\n')) {
            inputVector.push_back(line);
        }
    }
    cout << adjacentSymbol(inputVector, 0, 11) << '\n';
    // iterate through each line to find a number, at each digit check if it is next to a symbol.
    // if it is, then isPart = true. once we reach the end of the number, if isPart, add to the sum.
    int sum = 0;
    for(int j = 0; j < inputVector.size(); j++) {
        bool isPart = false;
        int val = 0;
        for(int i = 0; i < inputVector.at(0).length(); i++) {

            if(inputVector[j][i] >= '0' and inputVector[j][i] <= '9') {
                if(!isPart and adjacentSymbol(inputVector, j, i)) {
                    isPart = true;
                }
                val = val*10 + inputVector[j][i] - '0';
                if(i == inputVector[0].length()-1 and isPart) {
                    sum+=val;
                    isPart=false;
                    val=0;
                }

            } else {
                if(isPart) {
                    cout << val << '\n';
                    sum += val;
                }
                isPart = false;
                val = 0;
            }
        }
    }
    cout << sum;
    return sum;
}
