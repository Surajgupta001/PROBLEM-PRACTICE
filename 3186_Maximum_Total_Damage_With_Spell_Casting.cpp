/*
Maximum Total Damage With Spell Casting - [Leetcode - 3186(Medium)]
--------------------------------------------------------------------
A magician has various spells.

You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.

It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.

Each spell can be cast only once.

Return the maximum possible total damage that a magician can cast.

Example 1:

Input: power = [1,1,3,4]

Output: 6

Explanation:

The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.

Example 2:

Input: power = [7,1,6,6]

Output: 13

Explanation:

The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.

Constraints:

1 <= power.length <= 105
1 <= power[i] <= 109
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

// Approach - 1: Using Hashing + Recursion + Memoization
long long helper(vector<long long> &nums, int idx, unordered_map<long long, long long> mp, vector<long long> & dp){
    // Base case
    if(idx >= nums.size()) return 0;

    if(dp[idx] != -1) return dp[idx];

    // Skip
    long long skip = helper(nums, idx + 1, mp, dp);

    // Take
    long long j = lower_bound(nums.begin()+idx+1, nums.end(), nums[idx] + 3) - nums.begin();

    long long take = nums[idx]*mp[nums[idx]] + helper(nums, j, mp, dp);

    return dp[idx] = max(skip, take);
}

long long maximumTotalDamage(vector<int>& power) {
    unordered_map<long long, long long> mp; // to store frequency of each spell damage
    
    // Count frequency of each spell damage
    for(int &p : power){
        mp[p]++; // count frequency of each spell damage
    }
    
    vector<long long> nums(mp.size()); // to store unique spell damages
    for(auto &itr : mp){
        nums.push_back(itr.first);
    }
    
    sort(nums.begin(), nums.end()); // Sort unique spell damages

    int n = nums.size();
    
    vector<long long> dp(n+1, -1); // dp array for memoization

    return helper(nums, 0, mp, dp);

}


// Approach - 2: Using Hashing + Tabulation
long long maximumTotalDamage(vector<int>& power) {
    unordered_map<long long, long long> mp; // to store frequency of each spell damage
    
    // Count frequency of each spell damage
    for(int &p : power){
        mp[p]++; // count frequency of each spell damage
    }
    
    vector<long long> nums(mp.size()); // to store unique spell damages
    for(auto &itr : mp){
        nums.push_back(itr.first);
    }
    
    sort(nums.begin(), nums.end()); // Sort unique spell damages

    int n = nums.size();
    
    vector<long long> dp(n+1, 0); // dp array for tabulation
    
    long long result = INT_MIN;
    for(int i = n-1; i >= 0; i--){
        // Skip
        long long skip = (i+1 < n) ? dp[i+1] : 0;
        
        // Take
        long long j = lower_bound(nums.begin()+i+1, nums.end(), nums[i] + 3) - nums.begin();
        
        long long take = nums[i]*mp[nums[i]] + ((j < n) ? dp[j] : 0);
        
        dp[i] = max(skip, take);
        
        result = max(result, dp[i]);
    }
    return result;
}

int main() {
    
    vector<int> power = {7,1,6,6};
    
    cout << maximumTotalDamage(power) << endl; // Output: 13
    
    return 0;
}