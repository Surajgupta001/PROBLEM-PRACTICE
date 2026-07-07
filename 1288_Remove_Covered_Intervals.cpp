/*
Remove Covered Intervals - [Leetcode - 1288(Medium)]
--------------------------------------------------------

Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.

The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.

Return the number of remaining intervals.

Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Example 2:

Input: intervals = [[1,4],[2,3]]
Output: 1 

Constraints:

1 <= intervals.length <= 1000
intervals[i].length == 2
0 <= li < ri <= 10^5
All the given intervals are unique.
*/

#include <iostream>
#include <vector>
using namespace std;

static bool customComparator(vector<int> &a, vector<int> &b) {
    if (a[0] == b[0]) {
        return a[1] > b[1]; // Sort by ending point in descending order if starting points are equal
    }
    return a[0] < b[0]; // Sort by starting point in ascending order
}

int removeCoveredIntervals(vector<vector<int>>& intervals) {

    int n = intervals.size();

    // Sort based on the starting point of intervals, and if they are equal, sort based on the ending point in descending order
    sort(intervals.begin(), intervals.end(), customComparator);

    // vector<vector<int>> result;

    // result.push_back(intervals[0]); // Add the first interval to the result

    int lastIntervalEnd = intervals[0][1];
    int count = 1; // Count of remaining intervals

    // for(int i=1; i<n; i++){
    //     if(result.back()[1] >= intervals[i][1]) {
    //         // Current interval is covered by the last interval in result
    //         continue;
    //     } else {
    //         result.push_back(intervals[i]);
    //     }
    // }
    // return result.size();

    for(int i=1; i<n; i++){
        if(lastIntervalEnd >= intervals[i][1]) {
            // Current interval is covered by the last interval
            continue;
        } else {
            lastIntervalEnd = intervals[i][1]; // Update the end of the last interval
            count++; // Increment count of remaining intervals
        }
    }
    return count;
}

int main() {
    vector<vector<int>> intervals = {{1,4},{3,6},{2,8}};
    int remainingIntervals = removeCoveredIntervals(intervals);
    cout << "Number of remaining intervals: " << remainingIntervals << endl; // Output: 2
    return 0;
}