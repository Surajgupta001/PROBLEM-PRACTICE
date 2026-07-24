/*
Minimum Number of Flips to Make the Binary String Alternating - [Leetcode - 1888(Medium)]
------------------------------------------------------------------------------------------------
You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:

Type-1: Remove the character at the start of the string s and append it to the end of the string.
Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
Return the minimum number of type-2 operations you need to perform such that s becomes alternating.

The string is called alternating if no two adjacent characters are equal.

For example, the strings "010" and "1010" are alternating, while the string "0100" is not.

Example 1:

Input: s = "111000"
Output: 2
Explanation: Use the first operation two times to make s = "100011".
Then, use the second operation on the third and sixth elements to make s = "101010".

Example 2:

Input: s = "010"
Output: 0
Explanation: The string is already alternating.

Example 3:

Input: s = "1110"
Output: 1
Explanation: Use the second operation on the second element to make s = "1010".

Constraints:

1 <= s.length <= 10^5
s[i] is either '0' or '1'.
*/ 

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Approach : 1 s => s + s => sliding window of size n => check for min flips for both patterns 010101... and 101010...
int minFlips(string s) {
    int n = s.length();
    s = s + s; // Concatenate the string to itself to handle rotations

    // s1 = "01010101..."
    // s2 = "10101010..."

    string s1;
    string s2;
    for(int i=0; i<2*n; i++){
        s1 += (i % 2 == 0) ? '0' : '1';
        s2 += (i % 2 == 0) ? '1' : '0';
    }

    int flips1 = 0;
    int flips2 = 0;
    int result = INT_MAX;

    // Sliding window
    int i = 0;
    int j = 0;
    while(j < 2*n){
        if(s[j] != s1[j]) flips1++;
        if(s[j] != s2[j]) flips2++;

        if(j - i + 1 > n){// shrink the window size to n
            if(s[i] != s1[i]) flips1--;
            if(s[i] != s2[i]) flips2--;
            i++;
        }

        if(j - i + 1 == n){
            result = min({result, flips1, flips2});
        }

        j++;
    }
    return result;
}

// Approach : 2 - Not use s = s + s, use modulo to handle rotations
int minFlips(string s) {
    int n = s.length();

    // s1 = "01010101..."
    // s2 = "10101010..."

    string s1;
    string s2;
    for(int i=0; i<2*n; i++){
        s1 += (i % 2 == 0) ? '0' : '1';
        s2 += (i % 2 == 0) ? '1' : '0';
    }

    int flips1 = 0;
    int flips2 = 0;
    int result = INT_MAX;

    // Sliding window
    int i = 0;
    int j = 0;
    while(j < 2*n){
        if(s[j % n] != s1[j]) flips1++;
        if(s[j % n] != s2[j]) flips2++;

        if(j - i + 1 > n){// shrink the window size to n
            if(s[i % n] != s1[i]) flips1--;
            if(s[i % n] != s2[i]) flips2--;
            i++;
        }

        if(j - i + 1 == n){
            result = min({result, flips1, flips2});
        }

        j++;
    }
    return result;
}

// Approach : 3 -  without use of extra space for s1 and s2, use modulo to handle rotations
int minFlips(string s) {
    int n = s.length();

    int flips1 = 0; // flips for pattern starting with '0'
    int flips2 = 0; // flips for pattern starting with '1'
    int result = INT_MAX;

    // Sliding window
    int i = 0;
    int j = 0;
    while(j < 2*n){
        if(s[j % n] != (j % 2 == 0 ? '0' : '1')) flips1++;
        if(s[j % n] != (j % 2 == 0 ? '1' : '0')) flips2++;

        if(j - i + 1 > n){// shrink the window size to n
            if(s[i % n] != (i % 2 == 0 ? '0' : '1')) flips1--;
            if(s[i % n] != (i % 2 == 0 ? '1' : '0')) flips2--;
            i++;
        }

        if(j - i + 1 == n){
            result = min({result, flips1, flips2});
        }

        j++;
    }
    return result;
}

int main () {
    string s = "111000";
    cout << minFlips(s) << endl; // Output: 2

    s = "010";
    cout << minFlips(s) << endl; // Output: 0

    s = "1110";
    cout << minFlips(s) << endl; // Output: 1

    return 0;
}