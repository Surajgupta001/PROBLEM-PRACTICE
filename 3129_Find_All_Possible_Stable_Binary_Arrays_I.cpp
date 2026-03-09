/*
Find All Possible Stable Binary Arrays I - [Leetcode - 3129(Medium)]
------------------------------------------------------------------------
You are given 3 positive integers zero, one, and limit.

A binary array arr is called stable if:

The number of occurrences of 0 in arr is exactly zero.
The number of occurrences of 1 in arr is exactly one.
Each subarray of arr with a size greater than limit must contain both 0 and 1.
Return the total number of stable binary arrays.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: zero = 1, one = 1, limit = 2

Output: 2

Explanation:

The two possible stable binary arrays are [1,0] and [0,1], as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.

Example 2:

Input: zero = 1, one = 2, limit = 1

Output: 1

Explanation:

The only possible stable binary array is [1,0,1].

Note that the binary arrays [1,1,0] and [0,1,1] have subarrays of length 2 with identical elements, hence, they are not stable.

Example 3:

Input: zero = 3, one = 3, limit = 2

Output: 14

Explanation:

All the possible stable binary arrays are [0,0,1,0,1,1], [0,0,1,1,0,1], [0,1,0,0,1,1], [0,1,0,1,0,1], [0,1,0,1,1,0], [0,1,1,0,0,1], [0,1,1,0,1,0], [1,0,0,1,0,1], [1,0,0,1,1,0], [1,0,1,0,0,1], [1,0,1,0,1,0], [1,0,1,1,0,0], [1,1,0,0,1,0], and [1,1,0,1,0,0].



Constraints:

1 <= zero, one, limit <= 200
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mod = 1e9 + 7;

//Approach-1 (Recursion + Memoization)
//T.C : O(one * zero * limit)
//S.C : O(one * zero)
int helper(int onesLeft, int zerosLeft, bool lastWasOne, int limit, vector<vector<vector<int>>> &dp) {
    if(onesLeft == 0 && zerosLeft == 0) {
        return 1;
    }
    
    if(dp[onesLeft][zerosLeft][lastWasOne] != -1) {
        return dp[onesLeft][zerosLeft][lastWasOne];
    }
    
    int count = 0;
    
    if(lastWasOne == true) { //explore 0s
        for(int len = 1; len <= min(zerosLeft, limit); len++) {
            count = (count + helper(onesLeft, zerosLeft - len, false, limit, dp)) % mod;
        }
    } else { //explore 1s
        for(int len = 1; len <= min(onesLeft, limit); len++) {
            count = (count + helper(onesLeft - len, zerosLeft, true, limit, dp)) % mod;
        }
    }
    return dp[onesLeft][zerosLeft][lastWasOne] = count;
}

int numberOfStableArrays(int zero, int one, int limit) {
    vector<vector<vector<int>>> dp(one + 1, vector<vector<int>>(zero + 1, vector<int>(2, -1)));
    
    int startWithOne = helper(one, zero, false, limit, dp);
    int startWithZero = helper(one, zero, true, limit, dp);
    
    return (startWithOne + startWithZero) % mod;
}

// Approach-2 (Tabulation or Bottom-Up DP)
//T.C : O(one * zero * limit)
//S.C : O(one * zero)
int numberOfStableArrays(int zero, int one, int limit) {

    vector<vector<vector<int>>> dp(one + 1, vector<vector<int>>(zero + 1, vector<int>(2, 0)));

    // Base case: solve(0,0,lastWasOne) = 1
    dp[0][0][0] = 1; // lastWasOne = false
    dp[0][0][1] = 1; // lastWasOne = true

    for(int onesLeft = 0; onesLeft <= one; onesLeft++) {
        for(int zerosLeft = 0; zerosLeft <= zero; zerosLeft++) {

            if(onesLeft == 0 && zerosLeft == 0) continue;

            int count = 0;

            // if(lastWasOne == true) { explore 0s }
            count = 0;
            for(int len = 1; len <= min(zerosLeft, limit); len++) {
                count = (count + dp[onesLeft][zerosLeft - len][0]) % mod;
            }
            dp[onesLeft][zerosLeft][1] = count;

            // else { explore 1s }
            count = 0;
            for(int len = 1; len <= min(onesLeft, limit); len++) {
                count = (count + dp[onesLeft - len][zerosLeft][1]) % mod;
            }
            dp[onesLeft][zerosLeft][0] = count;
        }
    }

    int startWithOne  = dp[one][zero][false]; //solve(one, zero, false, limit);
    int startWithZero = dp[one][zero][true]; //solve(one, zero, true, limit);

    return (startWithOne + startWithZero) % mod;
}

int main(){
    int zero = 3, one = 3, limit = 2;
    cout << numberOfStableArrays(zero, one, limit) << endl; // Output: 14
    return 0;
}
