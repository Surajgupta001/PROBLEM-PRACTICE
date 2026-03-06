/*
Check if Binary String Has at Most One Segment of Ones - [Leetcode - 1784(easy)]
----------------------------------------------------------------------------------
Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.

Example 1:

Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.

Example 2:

Input: s = "110"
Output: true

Constraints:

1 <= s.length <= 100
s[i]​​​​ is either '0' or '1'.
s[0] is '1'.
*/

#include <iostream>
#include <vector>
using namespace std;

bool checkOnesSegment(string s) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1') {
            count++;
        } else {
            if (count > 0) {
                break;
            }
        }
    }
    return count == 0 || count == s.size() || s.find('1', s.find('0')) == string::npos;
}

int main() {
    string s1 = "1001";
    string s2 = "110";

    cout << checkOnesSegment(s1) << endl; // Output: false
    cout << checkOnesSegment(s2) << endl; // Output: true
    
    return 0;
}