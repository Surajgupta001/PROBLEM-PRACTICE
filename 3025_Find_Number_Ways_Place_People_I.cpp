/*
Find the Number of Ways to Place People I - [Leetcode - 3025]
---------------------------------------------------------------
You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].

Count the number of pairs of points (A, B), where

A is on the upper left side of B, and
there are no other points in the rectangle (or line) they make (including the border).
Return the count.

Example 1:

Input: points = [[1,1],[2,2],[3,3]]

Output: 0

Explanation:

There is no way to choose A and B so A is on the upper left side of B.

Example 2:

Input: points = [[6,2],[4,4],[2,6]]

Output: 2

Explanation:

The left one is the pair (points[1], points[0]), where points[1] is on the upper left side of points[0] and the rectangle is empty.
The middle one is the pair (points[2], points[1]), same as the left one it is a valid pair.
The right one is the pair (points[2], points[0]), where points[2] is on the upper left side of points[0], but points[1] is inside the rectangle so it's not a valid pair.
Example 3:

Input: points = [[3,1],[1,3],[1,1]]

Output: 2

Explanation:

The left one is the pair (points[2], points[0]), where points[2] is on the upper left side of points[0] and there are no other points on the line they form. Note that it is a valid state when the two points form a line.
The middle one is the pair (points[1], points[2]), it is a valid pair same as the left one.
The right one is the pair (points[1], points[0]), it is not a valid pair as points[2] is on the border of the rectangle.

Constraints:

2 <= n <= 50
points[i].length == 2
0 <= points[i][0], points[i][1] <= 50
All points[i] are distinct.
 
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Approach - 1: Brute Force
int numberOfPairs(vector<vector<int>>& points) {
    int n = points.size();
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        // A - Upper Wala points hai
        int x1 = points[i][0];
        int y1 = points[i][1];
        
        // B - Lower Wala points hai
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
        
            int x2 = points[j][0];
            int y2 = points[j][1];
        
            if (x1 <= x2 and y1 >= y2) {
                bool hasPointInside = false;
                for (int k = 0; k < n; k++) {
                    if (k == i or k == j) continue;
        
                    int x3 = points[k][0];
                    int y3 = points[k][1];
        
                    if (x3 >= x1 and x3 <= x2 and y3 <= y1 and y3 >= y2) {
                        hasPointInside = true;
                        break;
                    }
                }
        
                if (!hasPointInside) count++;
            }
        }
    }
    return count;
}

// Sort: x ascending, if x same then sort as y descending
bool customComparator(vector<int>& point1, vector<int>& point2) {
    if (point1[0] == point2[0]) {
        return point1[1] < point2[1];
    }
    return point1[0] < point2[0];
}

// Approach - 2: Slightly Improved
int numberOfPairs(vector<vector<int>>& points) {
    int n = points.size();
    int count = 0;

    // Sort points using the custom comparator
    sort(points.begin(), points.end(), customComparator);

    for (int i = 0; i < n; i++) {
        // A - Upper point
        int x1 = points[i][0];
        int y1 = points[i][1];

        int maxY = INT_MIN;
        // B - Find lower right points
        for (int j = i + 1; j < n; j++) {
            int x2 = points[j][0];
            int y2 = points[j][1];

            if (y2 > y1) continue; // Skip if point B is above A

            if (y2 >= maxY) {
                count++;
                maxY = y2;
            }
        }
    }
    return count;
}

int main() {
    
    vector<vector<int>> points = {{1,1},{2,2},{3,3}};
    cout << numberOfPairs(points) << endl;  // Output: 0
    
    points = {{6,2},{4,4},{2,6}};
    cout << numberOfPairs(points) << endl;  // Output: 2
    
    points = {{3,1},{1,3},{1,1}};
    cout << numberOfPairs(points) << endl;  // Output: 2
    
    return 0;
}