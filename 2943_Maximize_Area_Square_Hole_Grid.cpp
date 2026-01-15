/*
Maximize Area of Square Hole in Grid - [Leetcode - 2943(Medium)]
------------------------------------------------------------------
You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.

You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.

Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).

Example 1:

Input: n = 2, m = 1, hBars = [2,3], vBars = [2]

Output: 4

Explanation:

The left image shows the initial grid formed by the bars. The horizontal bars are [1,2,3,4], and the vertical bars are [1,2,3].

One way to get the maximum square-shaped hole is by removing horizontal bar 2 and vertical bar 2.

Example 2:

Input: n = 1, m = 1, hBars = [2], vBars = [2]

Output: 4

Explanation:

To get the maximum square-shaped hole, we remove horizontal bar 2 and vertical bar 2.

Example 3:

Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]

Output: 4

Explanation:

One way to get the maximum square-shaped hole is by removing horizontal bar 3, and vertical bar 4.

Constraints:

1 <= n <= 10^9
1 <= m <= 10^9
1 <= hBars.length <= 100
2 <= hBars[i] <= n + 1
1 <= vBars.length <= 100
2 <= vBars[i] <= m + 1
All values in hBars are distinct.
All values in vBars are distinct.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
    // 1st Step: Sort the inputs
    sort(hBars.begin(), hBars.end());
    sort(vBars.begin(), vBars.end());

    int maxConsecutiveHBars = 1; // Length of longest consecutive horizontal bars
    int maxConsecutiveVBars = 1; // Length of longest consecutive vertical bars

    // First find the Length of longest consecutive horizontal bars
    int currentConsecutiveHBars = 1;
    for(int i=1; i<hBars.size(); i++){
        if((hBars[i] - hBars[i-1]) == 1){
            currentConsecutiveHBars++;
        } else {
            currentConsecutiveHBars = 1;
        }
        maxConsecutiveHBars = max(maxConsecutiveHBars, currentConsecutiveHBars);
    }

    // Then find the Length of longest consecutive vertical bars
    int currentConsecutiveVBars = 1;
    for(int i=1; i<vBars.size(); i++){
        if((vBars[i] - vBars[i-1]) == 1){
            currentConsecutiveVBars++;
        } else {
            currentConsecutiveVBars = 1;
        }
        maxConsecutiveVBars = max(maxConsecutiveVBars, currentConsecutiveVBars);
    }

    // Square width and height must be same. We can reduce the larger one to match the smaller one.
    // So, take the minimum of both.
    int side = min(maxConsecutiveHBars, maxConsecutiveVBars) + 1; // +1 to account for the bars themselves
    
    return side * side; // Area of the square hole
}

int main() {
    int n1 = 2, m1 = 1;
    vector<int> hBars1 = {2, 3};
    vector<int> vBars1 = {2};
    cout << maximizeSquareHoleArea(n1, m1, hBars1, vBars1) << "\n"; // Output: 4

    int n2 = 1, m2 = 1;
    vector<int> hBars2 = {2};
    vector<int> vBars2 = {2};
    cout << maximizeSquareHoleArea(n2, m2, hBars2, vBars2) << "\n"; // Output: 4

    int n3 = 2, m3 = 3;
    vector<int> hBars3 = {2, 3};
    vector<int> vBars3 = {2, 4};
    cout << maximizeSquareHoleArea(n3, m3, hBars3, vBars3) << "\n"; // Output: 4

    return 0;
}