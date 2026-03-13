/*
Find All Possible Stable Binary Arrays II - [Leetcode - 3130(Hard)]
--------------------------------------------------------------------------
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

The two possible stable binary arrays are [1,0] and [0,1].

Example 2:

Input: zero = 1, one = 2, limit = 1

Output: 1

Explanation:

The only possible stable binary array is [1,0,1].

Example 3:

Input: zero = 3, one = 3, limit = 2

Output: 14

Explanation:

All the possible stable binary arrays are [0,0,1,0,1,1], [0,0,1,1,0,1], [0,1,0,0,1,1], [0,1,0,1,0,1], [0,1,0,1,1,0], [0,1,1,0,0,1], [0,1,1,0,1,0], [1,0,0,1,0,1], [1,0,0,1,1,0], [1,0,1,0,0,1], [1,0,1,0,1,0], [1,0,1,1,0,0], [1,1,0,0,1,0], and [1,1,0,1,0,0].

Constraints:

1 <= zero, one, limit <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mod = 1e9 + 7;

//Approach-2 (Bottom Up - Derived from Part-I)
//T.C : O(one * zero)
//S.C : O(one * zero)
int numberOfStableArrays(int zero, int one, int limit) {
    //dp[zero+1][one+1][2] 
    vector<vector<vector<int>>> dp(zero+1, vector<vector<int>>(one+1, vector<int>(2, 0)));
    
    for(int i = 0; i <= min(zero, limit); i++){
        dp[i][0][0] = 1;
    }
    
    for(int j = 0; j <= min(one, limit); j++) {
        dp[0][j][1] = 1;
    }

    for(int i = 0; i <= zero; i++) { //i = # 0s
        for(int j = 0; j <= one; j++) { //j = # 1s
            if(i == 0 || j == 0) continue;
            dp[i][j][1] = (dp[i][j-1][0] + dp[i][j-1][1]) % mod;
            
            if(j-1 >= limit) {
                dp[i][j][1] = (dp[i][j][1] - dp[i][j-1-limit][0] + mod) % mod;
            }

            dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % mod;
            
            if(i-1 >= limit) {
                dp[i][j][0] = (dp[i][j][0] - dp[i-1-limit][j][1] + mod) % mod;
            }
        }
    }
    return (dp[zero][one][0] + dp[zero][one][1]) % mod;
}

int main(){
    int zero = 3, one = 3, limit = 2;
    cout << numberOfStableArrays(zero, one, limit) << endl; // Output: 14

    return 0;
}