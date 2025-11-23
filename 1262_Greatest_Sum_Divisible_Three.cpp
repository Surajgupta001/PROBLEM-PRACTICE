/*
Greatest Sum Divisible by Three - [Leetcode - 1262(Medium)]
-------------------------------------------------------------
Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.

Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).

Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.
Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).

Constraints:

1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Approach - 1: Greedy Algorithm
int maxSumDivThree(vector<int>& nums) {
    int sum = 0;
    
    // Contains numbers which are giving remainder 1 when divided by 3
    vector<int> remainder1;
    
    // Contains numbers which are giving remainder 2 when divided by 3
    vector<int> remainder2;

    for(auto &num :nums){
        sum += num;
        if(num % 3 == 1){
            remainder1.push_back(num);
        }
        else if(num % 3 == 2){
            remainder2.push_back(num);
        }
    }

    if(sum % 3 == 0) return sum;

    // Sort both the remainder arrays because we need to remove the smallest elements possible
    sort(remainder1.begin(), remainder1.end());
    sort(remainder2.begin(), remainder2.end());

    int result = 0;

    int remainder = sum % 3; // Either 1 or 2

    if(remainder == 1){
        int remove1 = remainder1.size() >= 1 ? remainder1[0] : INT_MAX; // Smallest element from remainder1
        int remove2 = remainder2.size() >= 2 ? (remainder2[0] + remainder2[1]) : INT_MAX; // Sum of two smallest elements from remainder2
        
        result = max(result, sum - min(remove1, remove2));
    } 
    else {
        int remove1 = remainder2.size() >= 1 ? remainder2[0] : INT_MAX; // Smallest element from remainder2
        int remove2 = remainder1.size() >= 2 ? (remainder1[0] + remainder1[1]) : INT_MAX; // Sum of two smallest elements from remainder1

        result = max(result, sum - min(remove1, remove2));
    }
    return result;
}

// Approach - 2: Recursion + Memoization
int helper(int i, int remainder, vector<int>& nums, vector<vector<int>>& dp){
    if(i >= nums.size()){
        if(remainder == 0){
            return 0;
        }
        else{
            return INT_MIN;
        }
    }

    if (dp[i][remainder] != -1){
        return dp[i][remainder];
    }
    
    int take = nums[i] + helper(i + 1, (remainder + nums[i]) % 3, nums, dp);
    int skip = helper(i + 1, remainder, nums, dp);

    return dp[i][remainder] = max(take, skip);
}
    
int maxSumDivThree(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(3, -1));
    
    return helper(0, 0, nums, dp);
}
    
// Approach - 3: Bottom-Up Dynamic Programming
int maxSumDivThree(vector<int>& nums) {
    // dp[i][remainder] = maximum sum we can get using first i elements such that the sum % 3 = remainder

    int n = nums.size();

    vector<vector<int>> dp(n + 1, vector<int>(3, INT_MIN));

    dp[0][0] = 0; // Base case
    dp[0][1] = INT_MIN;
    dp[0][2] = INT_MIN;

    for(int i = n-1; i >= 0; i--){
        for(int remainder = 0; remainder <= 2; remainder++){
            int newRemainder = (remainder + nums[i]) % 3;
            int take = (dp[i + 1][newRemainder] == INT_MIN) ? INT_MIN : (nums[i] + dp[i + 1][newRemainder]);
            int skip = dp[i + 1][remainder];

            dp[i][remainder] = max(take, skip);
        }
    }
    return dp[0][0];
}

int main(){
    vector<int> nums = {3,6,5,1,8};
    cout << "Maximum Sum Divisible by Three: " << maxSumDivThree(nums) << endl;
    return 0;
}