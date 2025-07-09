/*
Maximum Number of Events That Can Be Attended II - [Leetcode - 1751(Hard)]
---------------------------------------------------------------------------
You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.

You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.

Return the maximum sum of values that you can receive by attending events.

 

Example 1:

Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.

Example 2:

Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.

Example 3:

Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
Output: 9
Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.

Constraints:

1 <= k <= events.length
1 <= k * events.length <= 106
1 <= startDayi <= endDayi <= 109
1 <= valuei <= 106
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Linear search approach with memoization
int helper(vector<vector<int>>& events, int idx, int k, int n, vector<vector<int>>& dp) {
    if (idx >= n || k <= 0) {
        return 0;
    }

    if (dp[idx][k] != -1) {
        return dp[idx][k];
    }

    int startingDay = events[idx][0]; // Starting day of the current event
    int endingDay = events[idx][1]; // Ending day of the current event
    int value = events[idx][2]; // Value of the current event

    int skip = helper(events, idx + 1, k, n, dp); // Skip the current event

    // Take the current event -> Linear search
    int j = idx + 1;
    for(; j < n ; j++) {
        if (events[j][0] > endingDay) { // Find the next event that starts after the current event ends
            break;
        }
    }

    int take = value + helper(events, j, k - 1, n, dp); // Take the current event and move to the next non-overlapping event

    return dp[idx][k] = max(skip, take); // Return the maximum of skipping or taking the current event
}

int maxValue(vector<vector<int>>& events, int k) {
    sort(events.begin(), events.end());
    int n = events.size();
    
    vector<vector<int>> dp(n, vector<int>(k + 1, -1)); // Initialize the DP table with -1

    return helper(events, 0, k, n, dp);
}

// Binary search approach to reduce the time complexity
int helper(vector<vector<int>>& events, int idx, int k, int n, vector<vector<int>>& dp) {
    if (idx >= n || k <= 0) {
        return 0;
    }

    if (dp[idx][k] != -1) {
        return dp[idx][k];
    }

    int startingDay = events[idx][0]; // Starting day of the current event
    int endingDay = events[idx][1]; // Ending day of the current event
    int value = events[idx][2]; // Value of the current event

    int skip = helper(events, idx + 1, k, n, dp); // Skip the current event

    // Take the current event -> Binary search
    int j = upper_bound(events.begin() + idx + 1, events.end(), vector<int>{endingDay, INT_MAX, INT_MAX}) - events.begin(); // Find the next event that starts after the current event ends

    int take = value + helper(events, j, k - 1, n, dp); // Take the current event and move to the next non-overlapping event

    return dp[idx][k] = max(skip, take); // Return the maximum of skipping or taking the current event
}

int maxValue(vector<vector<int>>& events, int k) {
    sort(events.begin(), events.end());
    int n = events.size();
    
    vector<vector<int>> dp(n, vector<int>(k + 1, -1)); // Initialize the DP table with -1

    return helper(events, 0, k, n, dp);
}

int main () {
    vector<vector<int>> events = {{1, 2, 4}, {3, 4, 3}, {2, 3, 1}};
    int k = 2;

    int result = maxValue(events, k);
    cout << "Maximum sum of values that can be received by attending events: " << result << endl;

    return 0;
}