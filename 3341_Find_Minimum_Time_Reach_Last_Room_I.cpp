/*
Find Minimum Time to Reach Last Room I - [Leetcode - 3341(Medium)]
-------------------------------------------------------------------
There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.

 

Example 1:

Input: moveTime = [[0,4],[4,4]]

Output: 6

Explanation:

The minimum time required is 6 seconds.

At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in one second.
Example 2:

Input: moveTime = [[0,0,0],[0,0,0]]

Output: 3

Explanation:

The minimum time required is 3 seconds.

At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in one second.
At time t == 2, move from room (1, 1) to room (1, 2) in one second.
Example 3:

Input: moveTime = [[0,1],[1,2]]

Output: 3

 

Constraints:

2 <= n == moveTime.length <= 50
2 <= m == moveTime[i].length <= 50
0 <= moveTime[i][j] <= 109
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; //{t, {i, j}}
// typedef pair<int, pair<int, int>> P;
int minTimeToReach(vector<vector<int>> &moveTime){
    int m = moveTime.size();
    int n = moveTime[0].size();

    vector<vector<int>> result(m, vector<int>(n, INT_MAX));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // all cells will be inserted in it (m*n)
    // priority_queue<P, vector<P>, greater<P>> pq; // all cells will be inserted in it (m*n)

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
                int wait = max(moveTime[nx][ny] - currTime, 0);
                int arrTime = currTime + wait + 1;

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

    vector<vector<int>> moveTime = {{0, 4}, {4, 4}};
    cout << minTimeToReach(moveTime) << endl; // Output: 6

    moveTime = {{0, 0, 0}, {0, 0, 0}};
    cout << minTimeToReach(moveTime) << endl; // Output: 3

    moveTime = {{0, 1}, {1, 2}};
    cout << minTimeToReach(moveTime) << endl; // Output: 3

    return 0;
}