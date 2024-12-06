#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

bool allZero(std::vector<int> arr, int n) {
    for(int i=0; i<n; i++) {
        if(arr[i] != 0) return false;
    }
    return true;
}

int findNext(std::vector<int> hist, int n) {
    // Base case, n==1, diff == 0, so pass 0 up the stack.
    if(n==1) return 0;
    // Calculate the differences between the passed numbers
    std::vector<int> diff;
    for(int i=1; i<n; i++) {
        diff.push_back(hist[i]-hist[i-1]);
    }
    // If all 0, then pass 0 up the stack.
    if(allZero(diff, n)) return 0;
    // If not all 0, then recurse down another level.
    return diff[n-2] + findNext(diff, n-1);
}

std::vector<int> extractNumbers(std::string line) {
    std::vector<int> numbers;
    int val = 0;
    bool readingNum = false;
    int isNegative = 1;
    for(int i = 0; i < line.length(); i++) {
        if('0' <= line[i] and line[i] <= '9') {
            val = val*10 + line[i]-'0';
            readingNum = true;
        }else if(line[i] == '-') {
            isNegative = -1;
        }else if (readingNum == true) {
            readingNum = false;
            numbers.push_back(isNegative*val);
            val = 0;
            isNegative = 1;
        }
    }
    if(readingNum) numbers.push_back(isNegative*val);
    return numbers;
}

int main() {
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle9/input.txt");
    std::string line;
    int sum = 0;
    while(getline(myFile, line, '\n')) {
        std::vector<int> numbers = extractNumbers(line);
        sum += numbers[numbers.size()-1] + findNext(numbers, numbers.size());
    }
    std::cout << sum << std::endl;
    return 0;
}
