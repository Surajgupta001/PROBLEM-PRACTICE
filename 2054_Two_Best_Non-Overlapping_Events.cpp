/*
Two Best Non-Overlapping Events - [Leetcode - 2054(Medium)]
-------------------------------------------------------------
You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.

Return this maximum sum.

Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.

Example 1:

Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.

Example 2:

Example 1 Diagram
Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5.

Example 3:

Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.
 
Constraints:

2 <= events.length <= 10^5
events[i].length == 3
1 <= startTimei <= endTimei <= 10^9
1 <= valuei <= 10^6

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Brute Force Approach
int maxTwoEvents(vector<vector<int>>& events) {
    int n = events.size();
    int result = 0;
    
    for(int i=0; i<n; i++){
        // Take event
        int value = events[i][2]; // Value of the current event
        result = max(result, value); // Update result if taking only this event is better

        for(int j=0; j<n; j++){
            if(i == j) continue; // Skip the same event
            
            if(events[j][0] <= events[i][1] && events[j][1] >= events[i][0]) continue; // Events overlap
            
            result = max(result, value + events[j][2]); // Update result if taking both events is better
        }
    }
    return result;
}

// Better Approach - Binary search + Recursion with Memoization
// Upperbound binary search to find the next valid event
int binarySearch(vector<vector<int>>& events, int endTime){
    int n = events.size();

    int low = 0;
    int high = n-1;

    int result = n; // Default to n if no valid event is found

    while(low <=high){
        int mid = low + (high - low)/2;

        if(events[mid][0] > endTime){
            result = mid; // Potential candidate
            high = mid - 1; // Look for a better candidate on the left side
        } else {
            low = mid + 1; // Move to the right side
        }
    }
    return result;
}

int helper(vector<vector<int>>& events, int i, int count, vector<vector<int>>& dp){
    int n = events.size();
    if(count == 2 || i >= n) return 0;
    
    if(dp[i][count] != -1) return dp[i][count];

    int nextValidElementIndex = binarySearch(events, events[i][1]);
    
    int take = events[i][2] + helper(events, nextValidElementIndex, count + 1, dp);
    int notTake = helper(events, i + 1, count, dp);

    return dp[i][count] = max(take, notTake);
}

int maxTwoEvents(vector<vector<int>>& events) {
    int n = events.size();
    
    sort(events.begin(), events.end()); // Sort events based on start time
    
    vector<vector<int>> dp(n, vector<int>(3, -1)); // Memoization table

    int count = 0;
    
    return helper(events, 0, count, dp);
}

int main() {
    vector<vector<int>> events1 = {{1,3,2},{4,5,2},{2,4,3}};
    cout << "Max Value (Example 1): " << maxTwoEvents(events1) << endl; // Output: 4

    vector<vector<int>> events2 = {{1,3,2},{4,5,2},{1,5,5}};
    cout << "Max Value (Example 2): " << maxTwoEvents(events2) << endl; // Output: 5

    vector<vector<int>> events3 = {{1,5,3},{1,5,1},{6,6,5}};
    cout << "Max Value (Example 3): " << maxTwoEvents(events3) << endl; // Output: 8

    return 0;
}