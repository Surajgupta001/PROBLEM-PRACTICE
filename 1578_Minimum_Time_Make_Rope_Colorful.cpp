/*
Minimum Time to Make Rope Colorful - [Leetcode - 1578(Medium)]
---------------------------------------------------------------
Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful. You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

Example 1:

Input: colors = "abaac", neededTime = [1,2,3,4,5]
Output: 3
Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
Bob can remove the blue balloon at index 2. This takes 3 seconds.
There are no longer two consecutive balloons of the same color. Total time = 3.

Example 2:

Input: colors = "abc", neededTime = [1,2,3]
Output: 0
Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.

Example 3:

Input: colors = "aabaa", neededTime = [1,2,3,4,1]
Output: 2
Explanation: Bob will remove the balloons at indices 0 and 4. Each balloons takes 1 second to remove.
There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.
 

Constraints:

n == colors.length == neededTime.length
1 <= n <= 10^5
1 <= neededTime[i] <= 10^4
colors contains only lowercase English letters.
*/ 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int minCost(string colors, vector<int>& neededTime) {
    int n = colors.length();

    int time = 0;
    int preMax = 0;

    for(int i = 0; i < n; i++){
        if(i > 0 && colors[i] != colors[i - 1]){
            preMax = 0;
        }

        int currTime = neededTime[i];
        time += min(preMax, currTime);
        preMax = max(preMax, currTime);
    }
    
    return time;
}

int main() {
    string colors1 = "abaac";
    vector<int> neededTime1 = {1, 2, 3, 4, 5};
    cout << "Minimum time for colors1: " << minCost(colors1, neededTime1) << endl; // Output: 3

    string colors2 = "abc";
    vector<int> neededTime2 = {1, 2, 3};
    cout << "Minimum time for colors2: " << minCost(colors2, neededTime2) << endl; // Output: 0

    string colors3 = "aabaa";
    vector<int> neededTime3 = {1, 2, 3, 4, 1};
    cout << "Minimum time for colors3: " << minCost(colors3, neededTime3) << endl; // Output: 2

    return 0;
}