#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int find_num(string line) {
    int first = -1;
    int firstNum = 0;
    int lastNum = 0;
    int last = 999;
    map<string, int> numMap{
        {"0", 0},
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
        {"zero", 0},
    };
    string options[]{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};
    for(string option: options) {
        int firstFind = line.find(option);
        int lastFind = line.rfind(option);
        if(firstFind != -1 and (firstFind < first or first == -1)) {
            first = firstFind;
            firstNum = numMap[option];
        }
        // can be both the first and last number.
        if(lastFind != -1 and (lastFind > last or last == 999)) {
            last = lastFind;
            lastNum = numMap[option];

        }
        // cout << option << '\n';
        // cout << firstFind << ' ' << lastFind << '\n';
        //
        // cout << first << ' ' << last << '\n';
        // cout << firstNum << ' ' << lastNum << '\n';
        // cout << '\n';
    }
    cout << firstNum*10 + lastNum << '\n';
    return firstNum * 10 + lastNum;
}
int main() {
    ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle1/input.txt");
    int sum = 0;
    if (!myFile) cerr << "Can't open input file!";
    if(myFile.is_open()) {
        string line;
        while(getline(myFile, line, '\n')) {
            cout << line << "\n";
            sum += find_num(line);
        }
        myFile.close();
    }
    cout << sum;
    return sum;
}
