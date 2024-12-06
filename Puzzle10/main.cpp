#include <fstream>
#include <iostream>
#include <vector>

struct traveller {
    int x;
    int y;
    char from;
};

void step(traveller &trav, const std::vector<std::string> &grid) {
    switch(grid[trav.y][trav.x]) {
        case 'L':
            if(trav.from == 'U') {
                trav.x = trav.x + 1;
                trav.from = 'L';
            } else {
                trav.y = trav.y - 1;
                trav.from = 'D';
            };
            break;
        case 'J':
            if(trav.from == 'U') {
                trav.x = trav.x - 1;
                trav.from = 'R';
            } else {
                trav.y = trav.y - 1;
                trav.from = 'D';
            }
            break;
        case '-':
            if(trav.from == 'L') {
                trav.x = trav.x + 1;
            } else {
                trav.x = trav.x - 1;
            }
            break;
        case '|':
            if(trav.from == 'U') {
                trav.y = trav.y + 1;
            } else {
                trav.y = trav.y - 1;
            }
            break;
        case '7':
            if(trav.from == 'L') {
                trav.y = trav.y + 1;
                trav.from = 'U';
            } else {
                trav.x = trav.x - 1;
                trav.from = 'R';
            }
            break;
        case 'F':
            if(trav.from == 'R') {
                trav.y = trav.y + 1;
                trav.from = 'U';
            } else {
                trav.x = trav.x + 1;
                trav.from = 'L';
            }
            break;
    }
}

int traversePipe(int start[2], const std::vector<std::string> &grid) {
    // first find the directions to travel
    traveller travellers[2];
    int nTravellers = 0;
    // left
    if(start[1] != 0 && ( grid[start[0]][start[1]-1] == '-' || grid[start[0]][start[1]-1] == 'F' || grid[start[0]][start[1]-1] == 'L') ) {
        travellers[nTravellers].y = start[0];
        travellers[nTravellers].x = start[1]-1;
        travellers[nTravellers].from = 'R';
        nTravellers++;
    }
    // right
    if(start[1] != grid[0].length() && ( grid[start[0]][start[1]+1] == '-' || grid[start[0]][start[1]+1] == '7' || grid[start[0]][start[1]+1] == 'J') ) {
        travellers[nTravellers].y = start[0];
        travellers[nTravellers].x = start[1]+1;
        travellers[nTravellers].from = 'L';
        nTravellers++;
    }
    // down
    if(start[0] != grid.size() && ( grid[start[0]+1][start[1]] == '|' || grid[start[0]+1][start[1]] == 'J' || grid[start[0]+1][start[1]] == 'L') ) {
        travellers[nTravellers].y = start[0]+1;
        travellers[nTravellers].x = start[1];
        travellers[nTravellers].from = 'U';
        nTravellers++;
    }
    // up
    if(start[0] != 0 && ( grid[start[0]-1][start[1]] == '|' || grid[start[0]-1][start[1]] == 'F' || grid[start[0]-1][start[1]] == '7') ) {
        travellers[nTravellers].y = start[0]-1;
        travellers[nTravellers].x = start[1];
        travellers[nTravellers].from = 'D';
    }
    int i = 1;
    while(travellers[0].x != travellers[1].x || travellers[0].y != travellers[1].y) {
        step(travellers[0], grid);
        step(travellers[1], grid);
        i++;
    }
    return i;
}
int main()
{
    std::ifstream myFile("/Users/dylanbeaumont/CLionProjects/AdventOfCode/Puzzle10/input.txt");
    std::string line;
    // construct a grid outlining the pipe
    // Find the starting point in the grid
    // initially get a valid direction then start.
    // at each point, find the valid paths (excluding where you came from) and step forward
    // keep iterating both directions along the pipe until you meet. The meeting point is the furthest point.
    std::vector<std::string> grid;
    grid.reserve(100);
    int i = 0;
    int start;
    int startPos[2];
    while(getline(myFile, line, '\n')) {
        grid.push_back(line);
        start = line.find_first_of('S');
        if(start != std::string::npos) {
            startPos[0] = i;
            startPos[1] = start;
        }
        i++;
    }
    std::cout << traversePipe(startPos, grid) << '\n';
}
