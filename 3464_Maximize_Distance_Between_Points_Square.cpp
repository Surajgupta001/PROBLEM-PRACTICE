/*
Maximize the Distance Between Points on a Square - [Leetcode - 3464(Hard)]
----------------------------------------------------------------------------
You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.

You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.

You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.

Return the maximum possible minimum Manhattan distance between the selected k points.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

Example 1:

Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

Output: 2

Explanation:

Select all four points.

Example 2:

Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

Output: 1

Explanation:

Select the points (0, 0), (2, 0), (2, 2), and (2, 1).

Example 3:

Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

Output: 1

Explanation:

Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).

Constraints:

1 <= side <= 10^9
4 <= points.length <= min(4 * side, 15 * 10^3)
points[i] == [xi, yi]
The input is generated such that:
points[i] lies on the boundary of the square.
All points[i] are unique.
4 <= k <= min(25, points.length)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// BRUTE FORCE + BACKTRACKING => TLE
int manhattanDistance(vector<int>& p1, vector<int>& p2) {
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

bool checkBruteForce(vector<vector<int>>& points, int k, int mid, int i, vector<int>& choosen) {
    if(choosen.size() == k){
        return true;
    }

    for(int p=i; p<points.size(); p++){
        bool valid = true;

        for(auto idx : choosen){
            if(manhattanDistance(points[p], points[idx]) < mid){
                valid = false;
                break;
            }
        }

        if(!valid){
            continue;
        }

        // Backtracking step
        choosen.push_back(p);
        if(checkBruteForce(points, k, mid, p + 1, choosen)){
            return true;
        }
        choosen.pop_back();
    }
    return false;
}

int maxDistanceBruteForce(int side, vector<vector<int>>& points, int k) {
    int low = 0;
    int high = 2 * side;
    
    int result = 0;

    while(low <= high){
        int mid = low + (high - low) / 2;

        vector<int> choosen; // store the index of the choosen points

        if(checkBruteForce(points, k, mid, 0, choosen)){
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

// OPTIMAL
long long get1DPosition(vector<int>& point, int side) {
    long long x = point[0];
    long long y = point[1];

    if(y == 0){
        return x; // bottom edge
    } else if(x == side){
        return side + y; // right edge
    } else if(y == side){
        return 3LL * side - x; // top edge
    } else {
        return 4LL * side - y; // left edge
    }
}

bool check(vector<long long>& doubled, int n, int k, int side, long long mid) {
    long long perimeter = 4LL * side;

    for(int i=0; i<n; i++){
        int count = 1; // picked one point
        int idx = i;

        long long lastPostion = doubled[i];

        for(int j=2; j<=k; j++){
            long long target = lastPostion + mid;

            auto itr = lower_bound((begin(doubled) + idx + 1), (begin(doubled) + i + n), target);
            if(itr == (begin(doubled) + i + n)){
                break;
            }
            idx = itr - begin(doubled);
            lastPostion = doubled[idx];
            count++;
        }
        if(count == k && (doubled[i] + perimeter - doubled[idx]) >= mid){
            return true;
        }
    }
    return false;
}

int maxDistance(int side, vector<vector<int>>& points, int k) {
    int n = points.size();
    long long perimeter = 4LL * side;

    vector<long long> positions(n); // store the position of the points on the boundary of the square

    for(int i=0; i<n; i++){
        positions[i] = get1DPosition(points[i], side);
    }

    sort(positions.begin(), positions.end());

    // Doubles the positions to handle the circular nature of the problem
    vector<long long> doubledPositions(2 * n);
    for(int i=0; i<n; i++){
        doubledPositions[i] = positions[i];
        doubledPositions[i + n] = positions[i] + perimeter;
    }

    int low = 0;
    int high = 2 * side;
    
    int result = 0;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(check(doubledPositions, n, k, side, mid)){
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}       

int main() {
    int side = 2;
    vector<vector<int>> points = {{0,0},{1,2},{2,0},{2,2},{2,1}};
    int k = 4;

    cout << maxDistance(side, points, k) << endl; // Output: 1

    return 0;
}