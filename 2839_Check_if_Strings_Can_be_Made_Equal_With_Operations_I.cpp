/*
Check if Strings Can be Made Equal With Operations I - [Leetcode - 2839(Easy)]
-------------------------------------------------------------------------------
You are given two strings s1 and s2, both of length 4, consisting of lowercase English letters.

You can apply the following operation on any of the two strings any number of times:

Choose any two indices i and j such that j - i = 2, then swap the two characters at those indices in the string.
Return true if you can make the strings s1 and s2 equal, and false otherwise.

Example 1:

Input: s1 = "abcd", s2 = "cdab"
Output: true
Explanation: We can do the following operations on s1:
- Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
- Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.

Example 2:

Input: s1 = "abcd", s2 = "dacb"
Output: false
Explanation: It is not possible to make the two strings equal.

Constraints:

s1.length == s2.length == 4
s1 and s2 consist only of lowercase English letters.
*/

#include <iostream>
#include <vector>
using namespace std;

// Approach - 1
bool canBeEqual(string s1, string s2) {
    int condition_1 = (s1[0] == s2[0] && s1[2] == s2[2]) || (s1[0] == s2[2] && s1[2] == s2[0]);
    
    int condition_2 = (s1[1] == s2[1] && s1[3] == s2[3]) || (s1[1] == s2[3] && s1[3] == s2[1]);
    
    return condition_1 && condition_2;
}

// Approach - 2
bool canBeEqual(string s1, string s2) {
    vector<int> even(26, 0);
    vector<int> odd(26, 0);

    for(int i=0; i<4; i++) {
        if(i % 2 == 0) {
            even[s1[i] - 'a']++;
            even[s2[i] - 'a']--;
        } else {
            odd[s1[i] - 'a']++;
            odd[s2[i] - 'a']--;
        }
    }

    for(int i=0; i<26; i++) {
        if(even[i] != 0 || odd[i] != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    string s1 = "abcd";
    string s2 = "cdab";
    
    bool result = canBeEqual(s1, s2);
    cout << (result ? "true" : "false") << endl; // Output: true
    
    return 0;
}