/*
Count Covered Buildings - [Leetcode - 3531(Medium)]
-----------------------------------------------------
You are given a positive integer n, representing an n x n city. You are also given a 2D grid buildings, where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].

A building is covered if there is at least one building in all four directions: left, right, above, and below.

Return the number of covered buildings.

 

Example 1:



Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]

Output: 1

Explanation:

Only building [2,2] is covered as it has at least one building:
above ([1,2])
below ([3,2])
left ([2,1])
right ([2,3])
Thus, the count of covered buildings is 1.

Example 2:

Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]

Output: 0

Explanation:

No building has at least one building in all four directions.

Example 3:

Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]

Output: 1

Explanation:

Only building [3,3] is covered as it has at least one building:
above ([1,3])
below ([5,3])
left ([3,2])
right ([3,5])
Thus, the count of covered buildings is 1.
 

Constraints:

2 <= n <= 10^5
1 <= buildings.length <= 105 
buildings[i] = [x, y]
1 <= x, y <= n
All coordinates of buildings are unique.
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
    unordered_map<int, pair<int, int>> yToMinMaxX;
    unordered_map<int, pair<int, int>> xToMinMaxY;

    for(auto &building : buildings) {
        int x = building[0];
        int y = building[1];

        if(!yToMinMaxX.count(y)){
            yToMinMaxX[y] = {INT_MAX, INT_MIN};
        }

        if(!xToMinMaxY.count(x)){
            xToMinMaxY[x] = {INT_MAX, INT_MIN};
        }

        yToMinMaxX[y].first = min(yToMinMaxX[y].first, x);
        yToMinMaxX[y].second = max(yToMinMaxX[y].second, x);
        
        xToMinMaxY[x].first = min(xToMinMaxY[x].first, y);
        xToMinMaxY[x].second = max(xToMinMaxY[x].second, y);
    }

    int  result = 0;

    for(auto &building : buildings){
        int x = building[0];
        int y = building[1];

        auto &xr = yToMinMaxX[y];
        auto &yr = xToMinMaxY[x];

        if(xr.first < x && x < xr.second && yr.first < y && y < yr.second){
            result++;
        }
    }

    return result;
}

int main() {
    int n = 3;
    vector<vector<int>> buildings = {{1,2},{2,2},{3,2},{2,1},{2,3}};
    cout << countCoveredBuildings(n, buildings) << endl; // Output: 1
    return 0;
}