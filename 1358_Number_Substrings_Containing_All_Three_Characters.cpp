/*
Number of Substrings Containing All Three Characters - [Leetcode - 1358(Medium)]
========================================================================================
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
*/ 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Sliding window approach
int numberOfSubstrings(string s){
    int n = s.length();
    vector<int> count(3, 0); // Count of 0 -> 'a', 1 ->'b', 2 -> 'c'

    int i = 0;
    int j = 0;

    int result = 0;

    while(j < n){
        count[s[j] - 'a']++; // Increment the count of the current character

        // Check if we have at least one of each character
        while(count[0] > 0 && count[1] > 0 && count[2] > 0){
            result += (n - j); // All substrings starting from i to j are valid
            count[s[i] - 'a']--; // Move i pointer to reduce the window size
            i++;
        }
        j++;
    }
    return result;
}

int main(){
    string s = "abcabc";
    cout << numberOfSubstrings(s) << endl;
    return 0;
}