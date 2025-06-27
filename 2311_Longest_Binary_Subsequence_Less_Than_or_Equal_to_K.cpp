/*
Longest Binary Subsequence Less Than or Equal to K - [Leetcode - 2311(Medium)]
-------------------------------------------------------------------------------
You are given a binary string s and a positive integer k.

Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.

Note:

The subsequence can contain leading zeroes.
The empty string is considered to be equal to 0.
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.


Example 1:

Input: s = "1001010", k = 5
Output: 5
Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
The length of this subsequence is 5, so 5 is returned.
Example 2:

Input: s = "00101001", k = 1
Output: 6
Explanation: "000001" is the longest subsequence of s that makes up a binary number less than or equal to 1, as this number is equal to 1 in decimal.
The length of this subsequence is 6, so 6 is returned.


Constraints:

1 <= s.length <= 1000
s[i] is either '0' or '1'.
1 <= k <= 109
*/

#include <iostream>
#include <string>
using namespace std;

// Recursion Approach
int helper(const string& str, int k, int idx, int n){
    if(idx == n) return 0; // Base case: reached the end of the string

    int take = 0;
    int bit = str[idx] - '0'; // Convert character to integer (0 or 1)
    long long value = (bit == 1 ? (1LL << (n - idx - 1)) : 0); // Calculate the value of the current bit in its position

    // If we take the current bit
    if(value <= k){
        take = 1 + helper(str, k - value, idx + 1, n); // Include this bit and reduce k accordingly
    }

    // If we don't take the current bit
    int skip = helper(str, k, idx + 1, n);

    return max(take, skip);
}

// Optimal Approach - Greedy Approach
int longestSubsequence(const string &s, int k){
    int length = 0;
    long long powerValue = 1;

    for (int i = s.size() - 1; i >= 0; --i){
        if (s[i] == '0'){
            length++;
        }
        else if (powerValue <= k){
            length++;
            k -= powerValue;
        }

        if (powerValue <= k) powerValue <<= 1; // powerValue *= 2;
    }

    return length;
}

int longestSubsequence(const string& s, int k){
    int n = s.length();
    return helper(s, k, 0, n);
}

int main() {
    string s = "1001010";
    int k = 5;
    cout << longestSubsequence(s, k) << endl;
    return 0;
}