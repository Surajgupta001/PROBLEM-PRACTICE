/*
Jump Game VII - [Leetcode - 1871(Medium)]
-------------------------------------------

You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

Example 1:

Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3. 
In the second step, move from index 3 to index 5.

Example 2:

Input: s = "01101110", minJump = 2, maxJump = 3
Output: false

Constraints:

2 <= s.length <= 10^5
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length
*/

#include <iostream>
#include <vector>
using namespace std;

// Approch-1: Recursion + Memoization -> TLE
int helper(int idx, string &s, int minJump, int maxJump, vector<int> &dp) {
    int n = s.length();
    
    if(idx == n - 1) {
        return true;
    }

    if(dp[idx] != -1) {
        return dp[idx];
    }

    for(int jump=minJump; jump<=maxJump; jump++){
        int j = idx + jump;

        if(j >= n ) break;

        if(s[j] == '0'){
            if(helper(j, s, minJump, maxJump, dp)) {
                return dp[idx] = true;
            }
        }
    }
    return dp[idx] = false;
}

// Approach-2: Bottom-Up DP -> TLE
bool canReach(string s, int minJump, int maxJump) {
    int n = s.length();

    vector<int> dp(n, false);

    // dp[i] => It is possible `i` to `(n-1)` => true, otherwise false false
    dp[n-1] = true;

    for(int i=n-1; i>=0; i--){
        for(int jump=minJump; jump<=maxJump; jump++){
            int j = i + jump;

            if(j >= n ) break;

            if(s[j] == '0'){
                if(dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    return dp[0];
}

// Approach-3: Optimal approach -> Sliding Window + DP -> O(n)
bool canReach(string s, int minJump, int maxJump) {
    int n = s.length();

    vector<int> dp(n, 0);
    // dp[i] => Number of ways to reach from `i` to `(n-1)`
    // dp[i] > 0 => Possible to reach from `i` to `(n-1)`, otherwise not possible

    dp[0] = 1;

    int count = 0;

    for(int j=1; j<n; j++){
        if(j - minJump >= 0){
            count += dp[j-minJump];
        }

        if(j - maxJump - 1 >= 0){
            count -= dp[j-maxJump-1];
        }

        if(count > 0 && s[j] == '0'){
            dp[j] = 1;
        }
    }
    return dp[n-1] > 0;
}

bool canReach(string s, int minJump, int maxJump) {
    int n = s.length();

    vector<int> dp(n, -1);
    return helper(0, s, minJump, maxJump, dp);
}

int main() {
    string s = "011010";
    int minJump = 2, maxJump = 3;

    cout << canReach(s, minJump, maxJump) << endl;

    return 0;
}