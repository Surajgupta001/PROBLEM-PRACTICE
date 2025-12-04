/*
Count Number of Trapezoids I - [LeetCode - 3623(Medium)]
----------------------------------------------------------
You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the ith point on the Cartesian plane.

A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if and only if they have the same slope.

Return the number of unique horizontal trapezoids that can be formed by choosing any four distinct points from points.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]

Output: 3

Explanation:
There are three distinct ways to pick four points that form a horizontal trapezoid:

Using points [1,0], [2,0], [3,2], and [2,2].
Using points [2,0], [3,0], [3,2], and [2,2].
Using points [1,0], [3,0], [3,2], and [2,2].

Example 2:

Input: points = [[0,0],[1,0],[0,1],[2,1]]

Output: 1

Explanation:
There is only one horizontal trapezoid that can be formed.

Constraints:

4 <= points.length <= 10^5
–10^8 <= xi, yi <= 10^8
All points are pairwise distinct.
*/ 

/*
Problem 3623 (Medium) - Horizontal Trapezoids Only
Constraint: Trapezoids must have at least one pair of horizontal sides (parallel to x-axis)
Approach: Count points at each y-coordinate, then form trapezoids by pairing horizontal lines at different y-levels
Formula: For each y-level with n points: nC2 horizontal lines, then multiply combinations from different y-levels
Complexity: O(n) - simple frequency counting
Input Size: Up to 10^5 points

*-------*    (top horizontal side)
/         \
*-----------*  (bottom horizontal side)
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int mod = 1e9 + 7;
int countTrapezoids(vector<vector<int>>& points) {
    unordered_map<int, int> map; // To store frequency of points at each corresponding y-coordinate

    // Count frequency of points for each y-coordinate
    for(auto &point : points){
        int y = point[1];
        map[y]++;
    }

    long long result = 0; // count of trapezoids
    long long prevHorizontalLines = 0; // To store count of horizontal lines formed by previous y-coordinates

    for(auto &itr: map){
        int count = itr.second;

        long long horizontalLines = (1LL * count * (count - 1)) / 2; // nC2 for current y-coordinate

        result += horizontalLines * prevHorizontalLines; // Multiply with previous horizontal lines to form trapezoids

        prevHorizontalLines += horizontalLines; // Update previous horizontal lines
    }
    return result % mod;
}

int main() {
    vector<vector<int>> points = {{1,0},{2,0},{3,0},{2,2},{3,2}};
    cout << countTrapezoids(points) << endl; // Output: 3
    return 0;
}