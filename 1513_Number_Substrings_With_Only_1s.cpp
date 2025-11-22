/*
Number of Substrings With Only 1s - [Leetcode - 1513(Easy)]
-------------------------------------------------------------
Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.

Example 1:

Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.

Example 2:

Input: s = "101"
Output: 2
Explanation: Substring "1" is shown 2 times in s.

Example 3:

Input: s = "111111"
Output: 21
Explanation: Each substring contains only 1's characters.
 
Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.
*/

#include <iostream>
#include <string>
using namespace std;

// Approach-1 (Simple maths formula to count substrings)
// T.C : O(n)
// S.C : O(1)

const int mod = 1e9 + 7;
int numSub(string s) {
    long long result = 0;
    long long count1 = 0;
    
    for (char ch : s){
        if (ch == '1'){
            count1++;
        }
        else{
            result = (result + count1 * (count1 + 1) / 2) % mod;
            count1 = 0;
        }
    }
    // Adding the last group of 1s
    result = (result + count1 * (count1 + 1) / 2) % mod;
    return (int)result;
}

// Approach-2 (Simple maths formula to count substrings)
// T.C : O(n)
// S.C : O(1)
int numSub(string s) {
    int result = 0;
    int count1 = 0;
    for (char ch : s){
        if (ch == '1'){
            count1++;
            result = (result + count1) % mod;
        }
        else{
            count1 = 0;
        }
    }
    return result;
}

int main() {
    string s1 = "0110111";
    string s2 = "101";
    string s3 = "111111";

    cout << "Number of substrings in s1: " << numSub(s1) << endl; // Output: 9
    cout << "Number of substrings in s2: " << numSub(s2) << endl; // Output: 2
    cout << "Number of substrings in s3: " << numSub(s3) << endl; // Output: 21

    return 0;
}