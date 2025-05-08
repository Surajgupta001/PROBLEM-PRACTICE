/*
Find Minimum Time to Reach Last Room II - [Leetcode - 3342(Medium)]
-------------------------------------------------------------------
There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.

Example 1:

Input: moveTime = [[0,4],[4,4]]

Output: 7

Explanation:

The minimum time required is 7 seconds.

At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
Example 2:

Input: moveTime = [[0,0,0,0],[0,0,0,0]]

Output: 6

Explanation:

The minimum time required is 6 seconds.

At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
At time t == 3, move from room (1, 1) to room (1, 2) in one second.
At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.
Example 3:

Input: moveTime = [[0,1],[1,2]]

Output: 4

Constraints:

2 <= n == moveTime.length <= 750
2 <= m == moveTime[i].length <= 750
0 <= moveTime[i][j] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

vector<vector<int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; //{t, {i, j}}
// typedef pair<int, pair<int, int>> P;
int minTimeToReach(vector<vector<int>> &moveTime){
    int m = moveTime.size();
    int n = moveTime[0].size();

    vector<vector<int>> result(m, vector<int>(n, INT_MAX));
    // priority_queue<P, vector<P>, greater<P>> pq; // all cells will be inserted in it (m*n)
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // all cells will be inserted in it (m*n)

    result[0][0] = 0;
    pq.push({0, {0, 0}});
    // S.C : O(m*n)
    while (!pq.empty()){ // O(m*n * log(m*n))
        int currTime = pq.top().first;
        auto cell = pq.top().second;
        int x = cell.first;
        int y = cell.second;

        pq.pop();
        if (x == m - 1 && y == n - 1){
            return currTime;
        }

        for (auto &dir : directions){
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n){
                int moveCost = (nx + ny) % 2 == 0 ? 2 : 1;
                int wait = max(moveTime[nx][ny] - currTime, 0);
                int arrTime = currTime + wait + moveCost;

                if (result[nx][ny] > arrTime){
                    result[nx][ny] = arrTime;
                    pq.push({arrTime, {nx, ny}});
                }
            }
        }
    }

    return -1;
}

int main(){
    vector<vector<int>> moveTime;

    // Test Case 1
    moveTime = {{0, 4}, {4, 4}};
    cout << "Minimum time to reach last room: " << minTimeToReach(moveTime) << endl; // Output: 7

    // Test Case 2
    moveTime = {{0, 0, 0, 0}, {0, 0, 0, 0}};
    cout << "Minimum time to reach last room: " << minTimeToReach(moveTime) << endl; // Output: 6

    // Test Case 3
    moveTime = {{0, 1}, {1, 2}};
    cout << "Minimum time to reach last room: " << minTimeToReach(moveTime) << endl; // Output: 4

    // Test Case 4
    moveTime = {{0, 58}, {27, 69}};
    cout << "Minimum time to reach last room: " << minTimeToReach(moveTime) << endl; // Output: 71

    return 0;
}