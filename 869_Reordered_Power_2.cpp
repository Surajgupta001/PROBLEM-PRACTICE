/*
Reordered Power of 2 - [Leetcode - 869(Medium)]
------------------------------------------------
You are given an integer n. We reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return true if and only if we can do this so that the resulting number is a power of two.

Example 1:

Input: n = 1
Output: true

Example 2:

Input: n = 10
Output: false
 
Constraints:

1 <= n <= 109
*/ 

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool reorderedPowerOf2(int n) {
    string s = to_string(n);
    sort(s.begin(), s.end());
    for (int i = 0; i < 31; i++) {
        string powerOf2 = to_string(1 << i);
        sort(powerOf2.begin(), powerOf2.end());
        if (s == powerOf2) return true;
    }
    return false;
}

int main () {
    int n = 10;
    if (reorderedPowerOf2(n)) {
        cout << n << " can be reordered to form a power of 2." << endl;
    } else {
        cout << n << " cannot be reordered to form a power of 2." << endl;
    }
    return 0;
}