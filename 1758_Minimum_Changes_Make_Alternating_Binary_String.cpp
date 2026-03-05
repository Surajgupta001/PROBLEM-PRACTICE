/*
Minimum Changes To Make Alternating Binary String - [Leetcode - 1758(Easy)]
------------------------------------------------------------------------------
You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Example 1:

Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.

Example 2:

Input: s = "10"
Output: 0
Explanation: s is already alternating.

Example 3:

Input: s = "1111"
Output: 2
Explanation: You need two operations to reach "0101" or "1010".

Constraints:

1 <= s.length <= 10^4
s[i] is either '0' or '1'.
*/

#include <iostream>
#include <string>
using namespace std;

int minOperations(string s) {
    int n = s.length();

    int start_with_0 = 0; // 01010101... Count of operations if we start with '0'
    int start_with_1 = 0; // 10101010... Count of operations if we start with '1'

    for(int i=0; i<n; i++){
        if(i % 2 == 0){ // Even
            if(s[i] == '0'){
                start_with_1++; // We want '1' at even index
            } else {
                start_with_0++; // We want '0' at even index
            }
        } else { // Odd
            if(s[i] == '1'){
                start_with_1++; // We want '0' at odd index
            } else {
                start_with_0++; // We want '1' at odd index
            }
        }
    }
    return min(start_with_0, start_with_1);
}

// Liitle Bit Better Approach:
int minOperations(string s) {
    int n = s.length();

    int start_with_0 = 0; // 01010101... Count of operations if we start with '0'

    for(int i=0; i<n; i++){
        if(i % 2 == 0){ // Even
            if(s[i] == '1'){
                start_with_0++; // We want '0' at even index
            }
        } else { // Odd
            if(s[i] == '0'){
                start_with_0++; // We want '1' at odd index
            }
        }
    }

    int start_with_1 = n - start_with_0; // Total length - operations needed for '0' pattern gives us operations needed for '1' pattern
    
    return min(start_with_0, start_with_1);
}

int main () {
    string s1 = "0100";
    cout << "Minimum operations to make '" << s1 << "' alternating: " << minOperations(s1) << endl;

    string s2 = "10";
    cout << "Minimum operations to make '" << s2 << "' alternating: " << minOperations(s2) << endl;

    string s3 = "1111";
    cout << "Minimum operations to make '" << s3 << "' alternating: " << minOperations(s3) << endl;

    return 0;
}