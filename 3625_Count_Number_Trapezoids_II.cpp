/*
Count Number of Trapezoids II - [LeetCode - 3625(Hard)]
----------------------------------------------------------
You are given a 2D integer array points where points[i] = [xi, yi] represents the coordinates of the ith point on the Cartesian plane.

Return the number of unique trapezoids that can be formed by choosing any four distinct points from points.

A trapezoid is a convex quadrilateral with at least one pair of parallel sides. Two lines are parallel if and only if they have the same slope.

Example 1:

Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]

Output: 2

Explanation:

There are two distinct ways to pick four points that form a trapezoid:

The points [-3,2], [2,3], [3,2], [2,-3] form one trapezoid.
The points [2,3], [3,2], [3,0], [2,-3] form another trapezoid.
Example 2:

Input: points = [[0,0],[1,0],[0,1],[2,1]]

Output: 1

Explanation:

There is only one trapezoid which can be formed.

Constraints:

4 <= points.length <= 500
–1000 <= xi, yi <= 1000
All points are pairwise distinct.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <map>
using namespace std;

int countTrapezoids(vector<vector<int>>& points) {
    int n = points.size();

    // Slope => {intercept}
    unordered_map<double, vector<double>> slopeIntercepts; // <slope, intercepts>

    unordered_map<int, vector<float>> midPointMap; // {midPointX*10000 + midPointY => {slopes}}

    int result = 0;

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int x1 = points[i][0];
            int y1 = points[i][1];

            int x2 = points[j][0];
            int y2 = points[j][1];

            int dx = x2 - x1;
            int dy = y2 - y1;

            float slope;
            float intercept;

            if(dx == 0){
                slope = INT_MAX;
                intercept = x1; // x = intercept
            }
            else{
                slope = (float)(y2-y1) / (x2-x1);
                intercept = (float)(y1*dx - x1*dy) / dx;
            }

            int midPointKey = (x1 + x2) * 10000 + (y1 + y2);

            slopeIntercepts[slope].push_back(intercept);

            midPointMap[midPointKey].push_back(slope);
        }
    }

    for(auto &itr : slopeIntercepts){
        if(itr.second.size() <= 1) continue;

        map<float, int> mp; // {intercept => count}
        for(double intercept : itr.second){
            mp[intercept]++;
        }

        int prevHorizontalLines = 0;

        for(auto &itr : mp){
            int count = itr.second;
            result += count * prevHorizontalLines; // counting duplicates also 
            prevHorizontalLines += count;
        }
    }

    for(auto &itr : midPointMap){
        if(itr.second.size() <= 1) continue;

        map<float, int> mp; // {slope => count}
        for(float slope : itr.second){
            mp[slope]++;
        }

        int prevHorizontalLines = 0;

        for(auto &itr : mp){
            int count = itr.second;
            result -= count * prevHorizontalLines; // removing duplicates
            prevHorizontalLines += count;
        }
    }
    return result;
}

int main (){
    vector<vector<int>> points1 = {{-3,2},{3,0},{2,3},{3,2},{2,-3}};
    cout << "Number of Trapezoids (Example 1): " << countTrapezoids(points1) << endl;

    vector<vector<int>> points2 = {{0,0},{1,0},{0,1},{2,1}};
    cout << "Number of Trapezoids (Example 2): " << countTrapezoids(points2) << endl;

    return 0;
}