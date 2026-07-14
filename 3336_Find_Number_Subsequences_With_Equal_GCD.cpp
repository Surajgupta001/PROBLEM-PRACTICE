/*
Find the Number of Subsequences With Equal GCD - [Leetcode - 3336(Hard)]
---------------------------------------------------------------------------

You are given an integer array nums.

Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:

The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
Return the total number of such pairs.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: nums = [1,2,3,4]

Output: 10

Explanation:

The subsequence pairs which have the GCD of their elements equal to 1 are:

([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])

Example 2:

Input: nums = [10,20,30]

Output: 2

Explanation:

The subsequence pairs which have the GCD of their elements equal to 10 are:

([10, 20, 30], [10, 20, 30])
([10, 20, 30], [10, 20, 30])
Example 3:

Input: nums = [1,1,1,1]

Output: 50

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 200
*/

#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9 + 7;

// Approach : 1 - Recursion + Memoization
int helper(vector<int>& nums, int i, int first, int second, vector<vector<vector<int>>>& dp) {
    if (i == static_cast<int>(nums.size())) {
        bool bothNonEmpty = (first != 0 && second != 0);
        bool gcdsMatch = (first == second);

        return (bothNonEmpty && gcdsMatch) ? 1 : 0;
    }

    if (dp[i][first][second] != -1) {
        return dp[i][first][second];
    }

    int skip = helper(nums, i + 1, first, second, dp); // no change in first and second

    int take1 = helper(nums, i + 1, __gcd(first, nums[i]), second, dp); // take in first

    int take2 = helper(nums, i + 1, first, __gcd(second, nums[i]), dp); // take in second

    return dp[i][first][second] = (skip + take1 + take2) % mod;
}

int subsequencePairCount(vector<int>& nums) {
    vector<vector<vector<int>>> dp(nums.size(), vector<vector<int>>(201, vector<int>(201, -1)));
    return helper(nums, 0, 0, 0, dp);
}

// Approach : 2 - Bottom Up DP
int subsequencePairCount(vector<int>& nums) {
    int n = nums.size();
    
    int maxElement = *max_element(nums.begin(), nums.end());
    
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(maxElement + 1, vector<int>(maxElement + 1, 0)));

    for(int first = 0; first <= maxElement; first++){
        for(int second = 0; second <= maxElement; second++){
            bool bothNonEmpty = (first != 0 && second != 0);
            bool gcdsMatch = (first == second);

            dp[n][first][second] = (bothNonEmpty && gcdsMatch) ? 1 : 0;
        }
    }

    for(int i = n - 1; i >= 0; i--){
        for(int first = 0; first <= maxElement; first++){
            for(int second = 0; second <= maxElement; second++){
                int skip = dp[i + 1][first][second]; // no change in first and second

                int take1 = dp[i + 1][__gcd(first, nums[i])][second]; // take in first

                int take2 = dp[i + 1][first][__gcd(second, nums[i])]; // take in second

                dp[i][first][second] = (0LL + skip + take1 + take2) % mod;
            }
        }
    }
    return dp[0][0][0];
}

// Approach : 3 - Space Optimized Bottom Up DP
int subsequencePairCount(vector<int>& nums) {
    int n = nums.size();

    int maxElement = *max_element(nums.begin(), nums.end());
    
    vector<vector<int>> prev(maxElement + 1, vector<int>(maxElement + 1, 0));

    for(int first = 0; first <= maxElement; first++){
        for(int second = 0; second <= maxElement; second++){
            bool bothNonEmpty = (first != 0 && second != 0);
            bool gcdsMatch = (first == second);

            prev[first][second] = (bothNonEmpty && gcdsMatch) ? 1 : 0;
        }
    }

    for(int i = n - 1; i >= 0; i--){
        vector<vector<int>> curr(maxElement + 1, vector<int>(maxElement + 1, 0));
        
        for(int first = 0; first <= maxElement; first++){
            for(int second = 0; second <= maxElement; second++){
                int skip = prev[first][second]; // no change in first and second

                int take1 = prev[__gcd(first, nums[i])][second]; // take in first

                int take2 = prev[first][__gcd(second, nums[i])]; // take in second

                curr[first][second] = (0LL + skip + take1 + take2) % mod;
            }
        }
        prev = move(curr);
    }
    
    return prev[0][0];
}

int  main() {
    vector<int> nums = {1, 2, 3, 4};
    cout << subsequencePairCount(nums) << endl; // Output: 10
    return 0;
}