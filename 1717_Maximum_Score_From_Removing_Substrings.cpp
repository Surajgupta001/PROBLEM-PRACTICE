/*
Maximum Score From Removing Substrings - [Leetcode - 1717(Medium)]
--------------------------------------------------------------------
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.

Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20
 

Constraints:

1 <= s.length <= 105
1 <= x, y <= 104
s consists of lowercase English letters.
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// Approach: 1 => Use a stack to remove substrings "ab" and "ba" iteratively.
string removeSubstr(string s, string &matchStr) {
    stack<char> st;
    
    for(auto &ch : s) {
        if(ch == matchStr[1] && !st.empty() && st.top() == matchStr[0]) {
            st.pop(); // Remove the last character if it forms the matchStr
        } else {
            st.push(ch); // Otherwise, push the character onto the stack
        }
    }

    string temp;
    while(!st.empty()){
        temp.push_back(st.top());
        st.pop();
    }

    // Reverse the string to get the correct order
    reverse(temp.begin(), temp.end());
    
    return temp;
}

// Approach: 2 => Without using a stack, we can use a two-pointer technique to remove substrings "ab" and "ba".
string removeSubstr(string s, string &matchStr) {
    int i=0; // used for writting purpose
    int j=0; // used for reading purpose

    for(j = 0; j < s.size(); j++){ // j is for reading each character
        s[i] = s[j]; // Writing on index i whatever j reads
        i++;

        if(i >= 2 && s[i-2] == matchStr[0] && s[i-1] == matchStr[1]){ // found matchStr before i
            i -= 2; // If the last two characters form the matchStr, remove them
        }
    }

    s.erase(s.begin() + i, s.end()); // Erase the remaining characters after i
    
    return s; // Return the modified string
}

int maximumGain(string s, int x, int y) {
    int n = s.size();
    int score = 0;

    string maxStr = (x > y) ? "ab" : "ba";
    string minStr = (x > y) ? "ba" : "ab";

    // 1st pass: remove maxStr
    string temp_first = removeSubstr(s, maxStr);
    int length = temp_first.size();

    int charRemoved = (n - length);

    score += (charRemoved / 2) * max(x, y);

    // 2nd pass: remove minStr
    string temp_second = removeSubstr(temp_first, minStr);
    charRemoved = (length - temp_second.size());

    score += (charRemoved / 2) * min(x, y);

    return score;
}

int main() {
    string s = "cdbcbbaaabab";
    int x = 4, y = 5;
    
    cout << "Maximum score: " << maximumGain(s, x, y) << endl; // Output: 19

    s = "aabbaaxybbaabb";
    x = 5, y = 4;
    
    cout << "Maximum score: " << maximumGain(s, x, y) << endl; // Output: 20

    return 0;
}