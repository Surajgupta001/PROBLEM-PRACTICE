/*
Maximum Difference by Remapping a Digit - [Leetcode - 2566(Easy)]
------------------------------------------------------------------
You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.

Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.

Notes:

When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
Bob can remap a digit to itself, in which case num does not change.
Bob can remap different digits for obtaining minimum and maximum values respectively.
The resulting number after remapping can contain leading zeroes.
 

Example 1:

Input: num = 11891
Output: 99009
Explanation: 
To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
The difference between these two numbers is 99009.

Example 2:

Input: num = 90
Output: 99
Explanation:
The maximum value that can be returned by the function is 99 (if 0 is replaced by 9) and the minimum value that can be returned by the function is 0 (if 9 is replaced by 0).
Thus, we return 99.
 

Constraints:

1 <= num <= 108
*/ 

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int minMaxDifference(int num) {
    string s = to_string(num);

    // For maximum
    string maxDigit = "";
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != '9') {
            maxDigit = s.substr(i, 1);
            break;
        }
    }
    string maxS = s;
    if (!maxDigit.empty()) {
        for (int i = 0; i < maxS.size(); ++i) {
            if (maxS.substr(i, 1) == maxDigit) {
                maxS[i] = '9';
            }
        }
    }

    // For minimum
    string minDigit = s.substr(0, 1);
    string minS = s;
    if (minDigit != "0") {
        for (int i = 0; i < minS.size(); ++i) {
            if (minS.substr(i, 1) == minDigit) {
                minS[i] = '0';
            }
        }
    }

    return stoi(maxS) - stoi(minS);
}

// Use of STL
int minMaxDifference(int num) {
    string str1 = to_string(num);
    string str2 = str1;
    
    // For maximum
    int idx = str1.find_first_not_of('9');
    if (idx != string::npos) {
        char ch = str1[idx];
        replace(str1.begin(), str1.end(), ch, '9');
    }

    // For minimum
    char ch = str2[0];
    replace(str2.begin(), str2.end(), ch, '0');

    return stoi(str1) - stoi(str2);
}

int main () {
    int num = 11891;
    cout << minMaxDifference(num) << endl;
}