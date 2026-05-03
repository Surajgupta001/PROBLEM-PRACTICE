/*
Walking Robot Simulation II - [Leetcode - 2069(Medium)]
----------------------------------------------------------
A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1, height - 1). The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). A robot is initially at cell (0, 0) facing direction "East".

The robot can be instructed to move for a specific number of steps. For each step, it does the following.

Attempts to move forward one cell in the direction it is facing.
If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and retries the step.
After the robot finishes moving the number of steps required, it stops and awaits the next instruction.

Implement the Robot class:

Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
void step(int num) Instructs the robot to move forward num steps.
int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".
 

Example 1:

example-1
Input
["Robot", "step", "step", "getPos", "getDir", "step", "step", "step", "getPos", "getDir"]
[[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
Output
[null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]

Explanation
Robot robot = new Robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
robot.step(2);  // It moves two steps East to (2, 0), and faces East.
robot.step(2);  // It moves two steps East to (4, 0), and faces East.
robot.getPos(); // return [4, 0]
robot.getDir(); // return "East"
robot.step(2);  // It moves one step East to (5, 0), and faces East.
                // Moving the next step East would be out of bounds, so it turns and faces North.
                // Then, it moves one step North to (5, 1), and faces North.
robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                // Then, it moves four steps West to (1, 2), and faces West.
robot.getPos(); // return [1, 2]
robot.getDir(); // return "West"

 

Constraints:

2 <= width, height <= 100
1 <= num <= 10^5
At most 10^4 calls in total will be made to step, getPos, and getDir.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Robot {
    public:
        
        int idx = 0;
        bool moved = false;
        vector<vector<int>> position; // Store the perimeter/boundary positions of the grid
        
        Robot(int width, int height) {
            // Bottom Row (Left to Right) -> East(0)
            for(int x=0; x<width; x++){
                position.push_back({x, 0, 0}); // {x, y, direction}
            }

            // Right Column (Bottom to Top) -> North(1)
            for(int y=1; y<height; y++){
                position.push_back({width-1, y, 1}); // {x, y, direction}
            }

            // Top Row (Right to Left) -> West(2)
            for(int x=width-2; x>=0; x--){
                position.push_back({x, height-1, 2}); // {x, y, direction}
            }

            // Left Column (Top to Bottom) -> South(3)
            for(int y=height-2; y>0; y--){
                position.push_back({0, y, 3}); // {x, y, direction}
            }

            // position = {{0, 0, 0}, ....}
            position[0][2] = 3; // Make it south for handling corner case when it comes back to (0, 0) after completing one full cycle around the perimeter

        }
        
        void step(int num) {
            moved = true;
            idx = (idx + num) % position.size();
        }
        
        vector<int> getPos() {
            return {position[idx][0], position[idx][1]};
        }
        
        string getDir() {
            if(!moved) return "East"; // Initial direction before any movement
            int dir = position[idx][2];
            if(dir == 0) return "East";
            else if(dir == 1) return "North";
            else if(dir == 2) return "West";
            else return "South";
        }
    };
    
/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */

int main() {
    Robot robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
    robot.step(2);  // It moves two steps East to (2, 0), and faces East.
    robot.step(2);  // It moves two steps East to (4, 0), and faces East.
    vector<int> pos1 = robot.getPos(); // return [4, 0]
    string dir1 = robot.getDir(); // return "East"
    cout << "Position: [" << pos1[0] << ", " << pos1[1] << "], Direction: " << dir1 << endl;

    robot.step(2);  // It moves one step East to (5, 0), and faces East.
                    // Moving the next step East would be out of bounds, so it turns and faces North.
                    // Then, it moves one step North to (5, 1), and faces North.
    robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
    robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                    // Then, it moves four steps West to (1, 2), and faces West.
    vector<int> pos2 = robot.getPos(); // return [1, 2]
    string dir2 = robot.getDir(); // return "West"
    cout << "Position: [" << pos2[0] << ", " << pos2[1] << "], Direction: " << dir2 << endl;

    return 0;
}