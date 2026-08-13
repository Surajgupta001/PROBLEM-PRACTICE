/*
Minimum Total Distance Traveled - [Leetcode - 2463(Hard)]
--------------------------------------------------------------
There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.

The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.

All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.

At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.

Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.

Note that

All robots move at the same speed.
If two robots move in the same direction, they will never collide.
If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
If the robot moved from a position x to a position y, the distance it moved is |y - x|.

Example 1:

Input: robot = [0,4,6], factory = [[2,2],[6,2]]
Output: 4
Explanation: As shown in the figure:
- The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
- The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
- The third robot at position 6 will be repaired at the second factory. It does not need to move.
The limit of the first factory is 2, and it fixed 2 robots.
The limit of the second factory is 2, and it fixed 1 robot.
The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.

Example 2:

Input: robot = [1,-1], factory = [[-2,1],[2,1]]
Output: 2
Explanation: As shown in the figure:
- The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
- The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
The limit of the first factory is 1, and it fixed 1 robot.
The limit of the second factory is 1, and it fixed 1 robot.
The total distance is |2 - 1| + |(-2) - (-1)| = 2. It can be shown that we cannot achieve a better total distance than 2.
 

Constraints:

1 <= robot.length, factory.length <= 100
factory[j].length == 2
-10^9 <= robot[i], positionj <= 10^9
0 <= limitj <= robot.length
The input will be generated such that it is always possible to repair every robot.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define ll long long

ll helper(int robot_index, int factory_index, vector<int>& robot, vector<int>& factory_positions, vector<vector<ll>>& dp) {
    int n = robot.size();
    int m = factory_positions.size();

    if(robot_index >= n) {
        return 0; //no more distance to be covered
    }
    
    if(factory_index >= m) {
        return 1e12;
    }

    if(dp[robot_index][factory_index] != -1) {
        return dp[robot_index][factory_index];
    }
    
    ll take_current_factory = abs(robot[robot_index] - factory_positions[factory_index]) + helper(robot_index+1, factory_index+1, robot, factory_positions, dp);
    ll skip = helper(robot_index, factory_index+1, robot, factory_positions, dp);
    
    return dp[robot_index][factory_index] = min(take_current_factory, skip);
}

long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
    //Step-1
    sort(begin(robot), end(robot));
    sort(begin(factory), end(factory));
    
    int m = robot.size();
    
    //Step-2 (Expand factory positions to avoid tracking of limit and easy recursion)
    vector<int> factory_positions;
    for(auto &f : factory) {
        int limit = f[1];
        int pos   = f[0];
        
        for(int j = 0; j < limit; j++) {
            factory_positions.push_back(pos);
        }
    }
    
    int n = factory_positions.size();
    vector<vector<ll>> dp(m+1, vector<ll>(n+1, -1));
    
    //step-3 (helper)
    return helper(0, 0, robot, factory_positions, dp);
}

int main() {
    vector<int> robot1 = {0, 4, 6};
    vector<vector<int>> factory1 = {{2, 2}, {6, 2}};
    cout << "Output: " << minimumTotalDistance(robot1, factory1) << endl; // Output: 4

    vector<int> robot2 = {1, -1};
    vector<vector<int>> factory2 = {{-2, 1}, {2, 1}};
    cout << "Output: " << minimumTotalDistance(robot2, factory2) << endl; // Output: 2

    return 0;
}