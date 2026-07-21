/*
Shuffle String - [Leetcode - 1528(Easy)]
---------------------------------------------

You are given a string s and an integer array indices of the same length. The string s will be shuffled such that the character at the ith position moves to indices[i] in the shuffled string.

Return the shuffled string. 

Example 1:

Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3]
Output: "leetcode"
Explanation: As shown, "codeleet" becomes "leetcode" after shuffling.

Example 2:

Input: s = "abc", indices = [0,1,2]
Output: "abc"
Explanation: After shuffling, each character remains in its position.

Constraints:

s.length == indices.length == n
1 <= n <= 100
s consists of only lowercase English letters.
0 <= indices[i] < n
All values of indices are unique.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

string restoreString(string s, vector<int>& indices) {
    int n = s.length();
    string shuffled(n, ' '); // Create a string of the same length as s, initialized with spaces
    for (int i = 0; i < n; ++i) {
        shuffled[indices[i]] = s[i]; // Place each character in its new position
    }
    return shuffled; // Return the shuffled string
}

// Using map
string restoreString(string s, vector<int>& indices) {
    int n = s.length();
    map<int, char> charMap;
    for (int i = 0; i < n; ++i) {
        charMap[indices[i]] = s[i];
    }
    string shuffled(n, ' ');
    for (auto& pair : charMap) {
        shuffled[pair.first] = pair.second;
    }
    return shuffled;
}

int main() {
    string s = "codeleet";
    vector<int> indices = {4,5,6,7,0,2,1,3};
    cout << restoreString(s, indices) << endl; // Output: "leetcode"
    return 0;
}