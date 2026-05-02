/*
Walking Robot Simulation - [Leetcode - 874(Medium)]
--------------------------------------------------------

A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:

-2: Turn left 90 degrees.
-1: Turn right 90 degrees.
1 <= k <= 9: Move forward k units, one unit at a time.
Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.

Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).

Note:

There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
North means +Y direction.
East means +X direction.
South means -Y direction.
West means -X direction.
 

Example 1:

Input: commands = [4,-1,3], obstacles = []

Output: 25

Explanation:

The robot starts at (0, 0):

Move north 4 units to (0, 4).
Turn right.
Move east 3 units to (3, 4).
The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.

Example 2:

Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]

Output: 65

Explanation:

The robot starts at (0, 0):

Move north 4 units to (0, 4).
Turn right.
Move east 1 unit and get blocked by the obstacle at (2, 4), robot is at (1, 4).
Turn left.
Move north 4 units to (1, 8).
The furthest point the robot ever gets from the origin is (1, 8), which squared is 12 + 82 = 65 units away.

Example 3:

Input: commands = [6,-1,-1,6], obstacles = [[0,0]]

Output: 36

Explanation:

The robot starts at (0, 0):

Move north 6 units to (0, 6).
Turn right.
Turn right.
Move south 5 units and get blocked by the obstacle at (0,0), robot is at (0, 1).
The furthest point the robot ever gets from the origin is (0, 6), which squared is 62 = 36 units away.

 

Constraints:

1 <= commands.length <= 10^4
commands[i] is either -2, -1, or an integer in the range [1, 9].
0 <= obstacles.length <= 10^4
-3 * 10^4 <= xi, yi <= 3 * 10^4
The answer is guaranteed to be less than 231.
*/

/*
========== IMPORTANT CONCEPTS ==========
    1. Direction Handling: 
        - The robot's direction is represented as a pair of integers (dx, dy). Initially, it points north (0, 1).
        - Turn Left 90 degrees: (dx, dy) becomes (-dy, dx).
        - Turn Right 90 degrees: (dx, dy) becomes (dy, -dx).
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    unordered_set<string> obs;
    for(vector<int> & obstacle : obstacles) {
        string key = to_string(obstacle[0]) + "," + to_string(obstacle[1]);
        obs.insert(key);
    }

    int x = 0;
    int y = 0;

    int maxDistance = 0;

    // Pointing to north
    pair<int, int> direction = {0, 1}; // North

    for(int i=0; i<commands.size(); i++){
        if(commands[i] == -2){
            // Turn left 90 degrees
            direction = {-direction.second, direction.first};
        } else if(commands[i] == -1){
            // Turn right 90 degrees
            direction = {direction.second, -direction.first};
        } else {
            // Move forward k units, one unit at a time
            for(int step=0; step<commands[i]; step++){
                int nextX = x + direction.first;
                int nextY = y + direction.second;

                string key = to_string(nextX) + "," + to_string(nextY);
                if(obs.find(key) == obs.end()){
                    // No obstacle, move to the next position
                    x = nextX;
                    y = nextY;

                    // Update max distance
                    maxDistance = max(maxDistance, x*x + y*y);
                } else {
                    // Obstacle found, stop moving in this direction
                    break;
                }
            }
        }
    }
    return maxDistance;
}

int main() {
    vector<int> commands1 = {4,-1,3};
    vector<vector<int>> obstacles1 = {};
    cout << robotSim(commands1, obstacles1) << endl; // Output: 25

    vector<int> commands2 = {4,-1,4,-2,4};
    vector<vector<int>> obstacles2 = {{2,4}};
    cout << robotSim(commands2, obstacles2) << endl; // Output: 65

    vector<int> commands3 = {6,-1,-1,6};
    vector<vector<int>> obstacles3 = {{0,0}};
    cout << robotSim(commands3, obstacles3) << endl; // Output: 36

    return 0;
}