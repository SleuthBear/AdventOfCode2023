#include <fstream>
#include <iostream>
#include <map>

std::map<char, int> cardValues = {{'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 1}, {'Q', 12}, {'K', 13}, {'A', 14}};

struct hand {
    std::string cards;
    int bid;
    int score;
};

hand getHand(std::string line) {
    std::map<char, int> cardMap = {
    {'2', 0}, {'3', 0}, {'4', 0}, {'5', 0},{'6', 0},{'7', 0},{'8', 0},{'9', 0},
        {'T', 0}, {'J', 0},{'Q', 0},{'K', 0},{'A', 0}};
    for(char c: line.substr(0,5)) {
        cardMap[c]++;
    }
    char max = 'K';
    for(auto const& [key, value]: cardMap) {
        if(value > cardMap[max] and key != 'J') max = key;
    }
    cardMap[max] += cardMap['J'];
    cardMap['J'] = 0;
    hand hand = {line.substr(0,5),
                    std::stoi(line.substr(6, line.length()-6)),
                    0};
    for(auto const& [key, value]: cardMap) {
        if(value == 5) {
            hand.score = 100;
            return hand;
        }
        if(value == 4) {
            hand.score = 80;
            return hand;
        }
        if(value == 3) {
            hand.score += 50;
        }
        if(value == 2) {
            hand.score += 20;
        }
    }
    return hand;
}

bool compareHands(hand hand1, hand hand2) {
    // return true is hand1 < hand2
    if(hand1.score == hand2.score) {
        for(int i = 0; i < 5; i++) {
            if(cardValues[hand1.cards[i]] < cardValues[hand2.cards[i]]) {
                return true;
            } else if(cardValues[hand1.cards[i]] > cardValues[hand2.cards[i]]) {
                return false;
            }
        }
        return false;
    }
    return hand1.score < hand2.score;
}


int main() {
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle7-2/input.txt");
    std::string line;
    std::vector<hand> rankings;
    while(getline(myFile, line, '\n')) {
        rankings.push_back(getHand(line));
    }
    std::sort(rankings.begin(), rankings.end(), compareHands);
    int rank = 1;
    unsigned long long sum = 0;
    for(hand h: rankings) {
        sum += rank*h.bid;
        std::cout << h.cards << ' ' << h.bid << '\n';
        rank++;
    }
    std::cout << sum << std::endl;
    return 0;
}
