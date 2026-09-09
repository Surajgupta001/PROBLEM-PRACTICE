/*
Minimum Moves to Clean the Classroom - [Leetcode - 3568(Medium)]
-------------------------------------------------------------------
You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:

'S': Starting position of the student
'L': Litter that must be collected (once collected, the cell becomes empty)
'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
'X': Obstacle the student cannot pass through
'.': Empty space
You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.

Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.

Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.

Example 1:

Input: classroom = ["S.", "XL"], energy = 2

Output: 2

Explanation:

The student starts at cell (0, 0) with 2 units of energy.
Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
The student collects all the litter using 2 moves. Thus, the output is 2.
Example 2:

Input: classroom = ["LS", "RL"], energy = 4

Output: 3

Explanation:

The student starts at cell (0, 1) with 4 units of energy.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of energy used and 3 units remaining.
Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to 4.
Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
The student collects all the litter using 3 moves. Thus, the output is 3.
Example 3:

Input: classroom = ["L.S", "RXL"], energy = 3

Output: -1

Explanation:

No valid path collects all 'L'.

Constraints:

1 <= m == classroom.length <= 20
1 <= n == classroom[i].length <= 20
classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
1 <= energy <= 50
There is exactly one 'S' in the grid.
There are at most 10 'L' cells in the grid.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class state {
public:
    int row;
    int col;
    int energyLeft;
    int collectedListMask;
};

vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

int minMoves(vector<string>& classroom, int energy) {
    int m = classroom.size();        
    int n = classroom[0].size();

    int maxEnergy = energy;

    vector<vector<int>> litterBit(m, vector<int>(n));
    int litterCount = 0;
    int startRow = 0;
    int startCol = 0;

    for(int r=0; r<m; r++){
        for(int c=0; c<n; c++){
            litterBit[r][c] = -1;
            if(classroom[r][c] == 'S'){
                startRow = r;
                startCol = c;
            } else if(classroom[r][c] == 'L'){
                litterBit[r][c] = litterCount; // 0th position, 1st position, 2nd position, etc.
                litterCount++;
            }
        }
    }

    int allCollected = (1 << litterCount) - 1; // 2^litterCount - 1
    if(litterCount == 0) return 0; // No litter to collect

    // Use BFS to find the minimum number of moves
    queue<state> qu;
    qu.push({startRow, startCol, maxEnergy, 0});

    // visited[r][c][energy][mask] = true means we have already visited cell (r, c) with energy and collected litter mask -> 4D vector
    vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(maxEnergy + 1, vector<bool>(1 << litterCount, false))));
    visited[startRow][startCol][maxEnergy][0] = true;

    int moves = 0;
    while(!qu.empty()){
        int currSize = qu.size();

        while(currSize--){
            state curr = qu.front();
            qu.pop();

            if(curr.collectedListMask == allCollected){
                return moves; // All litter collected
            }

            if(curr.energyLeft == 0) continue; // Cannot move further if energy is 0

            // Explore all 4 directions
            for(auto &dir : directions){
                int newRow = curr.row + dir[0];
                int newCol = curr.col + dir[1];

                // Check boundaries and obstacles
                if(newRow < 0 || newRow >= m || newCol < 0 || newCol >= n || classroom[newRow][newCol] == 'X'){
                    continue;
                }

                char cell = classroom[newRow][newCol];
                if(cell == 'X') continue; // Cannot move to obstacle
                
                int nextEnergy = curr.energyLeft - 1;
                int nextMask = curr.collectedListMask;

                if(cell == 'R'){
                    nextEnergy = maxEnergy; // Reset energy
                } else if(cell == 'L'){
                    nextMask |= (1 << litterBit[newRow][newCol]); // Collect litter
                }

                if(!visited[newRow][newCol][nextEnergy][nextMask]){
                    visited[newRow][newCol][nextEnergy][nextMask] = true;
                    qu.push({newRow, newCol, nextEnergy, nextMask});
                }
            }
        }
        moves++;
    }
    return -1; // Impossible to collect all litter
}

int main() {
    vector<string> classroom1 = {"S.", "XL"};
    int energy1 = 2;
    cout << minMoves(classroom1, energy1) << endl; // Output: 2

    vector<string> classroom2 = {"LS", "RL"};
    int energy2 = 4;
    cout << minMoves(classroom2, energy2) << endl; // Output: 3

    vector<string> classroom3 = {"L.S", "RXL"};
    int energy3 = 3;
    cout << minMoves(classroom3, energy3) << endl; // Output: -1

    return 0;
}