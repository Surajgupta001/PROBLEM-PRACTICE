/*
Count Partitions With Max-Min Difference at Most K - [Leetcode - 3578(Medium ❎ Hard ✔️)]
-------------------------------------------------------------------------------------------
You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.

Return the total number of ways to partition nums under this condition.

Since the answer may be too large, return it modulo 109 + 7.

Example 1:

Input: nums = [9,4,1,3,7], k = 4

Output: 6

Explanation:

There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:

[[9], [4], [1], [3], [7]]
[[9], [4], [1], [3, 7]]
[[9], [4], [1, 3], [7]]
[[9], [4, 1], [3], [7]]
[[9], [4, 1], [3, 7]]
[[9], [4, 1, 3], [7]]

Example 2:

Input: nums = [3,3,4], k = 0

Output: 2

Explanation:

There are 2 valid partitions that satisfy the given conditions:

[[3], [3], [4]]
[[3, 3], [4]]
 

Constraints:

2 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^9
0 <= k <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <deque>
using namespace std;

#define ll long long

int mod = 1e9 + 7;

// Recursion + Memoization
ll solve(int i, vector<int>& nums, int k, vector<ll>& dp) {
    if(i >= nums.size()) {
        return 1;
    }

    if(dp[i] != -1) {
        return dp[i];       
    }

    int count = 0;
    int minElement = INT_MAX;
    int maxElement = INT_MIN;

    for(int j = i; j < nums.size(); j++){
        minElement = min(minElement, nums[j]);
        maxElement = max(maxElement, nums[j]);

        if(maxElement - minElement <= k){
            count = (count + solve(j + 1, nums, k, dp)) % mod;
        }
        else{
            break;
        }
    }
    return dp[i] = count;
}

int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> dp(n, -1);
    return solve(0, nums, k, dp);
}

// Bottom-Up DP
int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> dp(n + 1, 0);
    dp[n] = 1; // base case

    for(int i = n - 1; i >= 0; i--) {
        int minElement = INT_MAX;
        int maxElement = INT_MIN;

        for(int j = i; j < n; j++) {
            minElement = min(minElement, nums[j]);
            maxElement = max(maxElement, nums[j]);

            if(maxElement - minElement <= k) {
                dp[i] = (dp[i] + dp[j + 1]) % mod;
            }
            else {
                break;
            }
        }
    }
    return dp[0];
}

// Optimized Bottom-Up DP using Deque and Sliding Window
int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n + 1, 0);
    vector<int> prefixSum(n + 1, 0);

    dp[0] = 1; // base case
    prefixSum[0] = 1; // prefix sum of dp

    deque<int> minDeque; // will store indices of elements in increasing order
    deque<int> maxDeque; // will store indices of elements in decreasing order

    int i = 0;
    int j = 0;

    while(j < n){
        while(not maxDeque.empty() and nums[j] > nums[maxDeque.back()]){
            maxDeque.pop_back();
        }
        maxDeque.push_back(j);

        while(not minDeque.empty() and nums[j] < nums[minDeque.back()]){
            minDeque.pop_back();
        }
        minDeque.push_back(j);

        while(i <=j and  nums[maxDeque.front()] - nums[minDeque.front()] > k){
            i++;
            if(not maxDeque.empty() and maxDeque.front() < i){
                maxDeque.pop_front();
            }
            if(not minDeque.empty() and minDeque.front() < i){
                minDeque.pop_front();
            }
        }
        
        dp[j + 1] = (prefixSum[j] - (i > 0 ? prefixSum[i - 1] : 0) + mod) % mod;
        prefixSum[j + 1] = (prefixSum[j] + dp[j + 1]) % mod;
        
        j++;
    }
    return dp[n];
}

int main() {
    vector<int> nums = {9, 4, 1, 3, 7};
    int k = 4;
    cout << countPartitions(nums, k) << endl; // Output: 6
    return 0;
}