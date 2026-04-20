/*
Maximum Walls Destroyed by Robots - [Leetcode - 3661]
---------------------------------------------------------
There is an endless straight line populated with some robots and walls. You are given integer arrays robots, distance, and walls:

robots[i] is the position of the ith robot.
distance[i] is the maximum distance the ith robot's bullet can travel.
walls[j] is the position of the jth wall.

Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it immediately stops at that robot and cannot continue.

Return the maximum number of unique walls that can be destroyed by the robots.

Notes:

A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
Robots are not destroyed by bullets.

Example 1:

Input: robots = [4], distance = [3], walls = [1,10]

Output: 1

Explanation:

robots[0] = 4 fires left with distance[0] = 3, covering [1, 4] and destroys walls[0] = 1.
Thus, the answer is 1.
Example 2:

Input: robots = [10,2], distance = [5,1], walls = [5,2,7]

Output: 3

Explanation:

robots[0] = 10 fires left with distance[0] = 5, covering [5, 10] and destroys walls[0] = 5 and walls[2] = 7.
robots[1] = 2 fires left with distance[1] = 1, covering [1, 2] and destroys walls[1] = 2.
Thus, the answer is 3.
Example 3:
Input: robots = [1,2], distance = [100,1], walls = [10]

Output: 0

Explanation:

In this example, only robots[0] can reach the wall, but its shot to the right is blocked by robots[1]; thus the answer is 0.

Constraints:

1 <= robots.length == distance.length <= 10^5
1 <= walls.length <= 10^5
1 <= robots[i], walls[j] <= 10^9
1 <= distance[i] <= 10^5
All values in robots are unique
All values in walls are unique
*/

// Preventing Double Counting Overlaps with DP
// Linear DP Sweep over Isolated Segments

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countWalls(vector<int>& walls, int l, int r) {
    int left = lower_bound(walls.begin(), walls.end(), l) - walls.begin();
    int right = upper_bound(walls.begin(), walls.end(), r) - walls.begin();

    return right - left; // Number of walls in the range [l, r]
}

int helper(vector<int>& walls, vector<pair<int, int>>& robotDist, vector<pair<int, int>>& ranges, int i, int prevDir, vector<vector<int>>& dp) {
    if(i == robotDist.size()) return 0;

    if(dp[i][prevDir] != -1) return dp[i][prevDir];
    
    int leftStart = ranges[i].first; // Start of the left range for the current robot

    if(prevDir == 1){ // prev robot fired bullet towards right
        leftStart = max(leftStart, ranges[i-1].second + 1); // Ensure we start from the right of the previous robot's range
    }

    int leftTake = countWalls(walls, leftStart, robotDist[i].first) + helper(walls, robotDist, ranges, i+1, 0, dp); // 0 => current robot fires left
    int rightTake = countWalls(walls, robotDist[i].first, ranges[i].second) + helper(walls, robotDist, ranges, i+1, 1, dp); // 1 => current robot fires right

    return dp[i][prevDir] = max(leftTake, rightTake);    
}

int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
    int n = robots.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));

    // Create a vector of pairs to store robot positions and their corresponding distances
    vector<pair<int, int>> robotDist(n); // {robotPosition, distance}
    for(int i = 0; i < n; i++) {
        robotDist[i] = {robots[i], distance[i]};
    }

    // Sort the robotDist vector based on robot positions
    sort(robotDist.begin(), robotDist.end());
    sort(walls.begin(), walls.end());

    // Prepare range vectors for each robot
    vector<pair<int, int>> ranges(n); // {leftRange, rightRange}
    for(int i=0; i<n; i++){
        int pos = robotDist[i].first;
        int dist = robotDist[i].second;
        
        int leftLimit = (i == 0) ? 1 : robotDist[i-1].first + 1; // Left limit is either 1 or just after the previous robot
        int rightLimit = (i == n-1) ? 1e9 : robotDist[i+1].first - 1; // Right limit is either 1e9 or just before the next robot

        int leftRange = max(pos - dist, leftLimit);
        int rightRange = min(pos + dist, rightLimit);

        ranges[i] = {leftRange, rightRange};
    }

    // prev = 0/1 => previous robot's position is either to the left or right of the current robot
    return helper(walls, robotDist, ranges, 0, 0, dp);
}

int main() {
    vector<int> robots = {10, 2};
    vector<int> distance = {5, 1};
    vector<int> walls = {5, 2, 7};

    cout << maxWalls(robots, distance, walls) << endl; // Output: 3

    return 0;
}