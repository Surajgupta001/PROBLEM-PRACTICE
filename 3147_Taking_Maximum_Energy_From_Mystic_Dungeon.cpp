/*
Taking Maximum Energy From the Mystic Dungeon - [LeetCode - 3147(Medium)]
---------------------------------------------------------------------------
In a mystic dungeon, n magicians are standing in a line. Each magician has an attribute that gives you energy. Some magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician i, you will be instantly transported to magician (i + k). This process will be repeated until you reach the magician where (i + k) does not exist.

In other words, you will choose a starting point and then teleport with k jumps until you reach the end of the magicians' sequence, absorbing all the energy during the journey.

You are given an array energy and an integer k. Return the maximum possible energy you can gain.

Note that when you are reach a magician, you must take energy from them, whether it is negative or positive energy.

Example 1:

Input: energy = [5,2,-10,-5,1], k = 3

Output: 3

Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

Example 2:

Input: energy = [-2,-3,-1], k = 2

Output: -1

Explanation: We can gain a total energy of -1 by starting from magician 2.

 

Constraints:

1 <= energy.length <= 105
-1000 <= energy[i] <= 1000
1 <= k <= energy.length - 1
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Approach - 1: Recursion + Memoization (Top-Down DP)
int helper(vector<int>& energy, int k, int i, vector<int>& dp) {
    int n = energy.size();
    
    if (i >= n) return 0;
    
    if (dp[i] != INT_MIN) return dp[i];

    return dp[i] = energy[i] + helper(energy, k, i + k, dp);
}

int maximumEnergy(vector<int>& energy, int k) {
    int n = energy.size();
    
    vector<int> dp(n, INT_MIN);
    
    int maxEnergy = INT_MIN;

    for (int i = 0; i < n; i++) {
        maxEnergy = max(maxEnergy, helper(energy, k, i, dp));
    }

    return maxEnergy;
}

// Approach - 2: Tabulation (Bottom-Up DP)
int maximumEnergy(vector<int>& energy, int k) {
    int n = energy.size();
    
    vector<int> dp(n, INT_MIN);
    
    int maxEnergy = INT_MIN;

    for (int i = n - 1; i >= 0; i--) {
        if (i + k < n) {
            dp[i] = energy[i] + dp[i + k];
        } else {
            dp[i] = energy[i];
        }
        maxEnergy = max(maxEnergy, dp[i]);
    }

    return maxEnergy;       
}

int main() {
    vector<int> energy = {5, 2, -10, -5, 1};
    int k = 3;
    cout << "Maximum Energy: " << maximumEnergy(energy, k) << endl; // Output: 3
    return 0;
}