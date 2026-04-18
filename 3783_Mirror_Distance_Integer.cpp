/*
Mirror Distance of an Integer - [Leetcode - 3783(Easy)]
-----------------------------------------------------------
You are given an integer n.

Define its mirror distance as: abs(n - reverse(n))​​​​​​​ where reverse(n) is the integer formed by reversing the digits of n.

Return an integer denoting the mirror distance of n​​​​​​​.

abs(x) denotes the absolute value of x.

Example 1:

Input: n = 25

Output: 27

Explanation:

reverse(25) = 52.
Thus, the answer is abs(25 - 52) = 27.

Example 2:

Input: n = 10

Output: 9

Explanation:

reverse(10) = 01 which is 1.
Thus, the answer is abs(10 - 1) = 9.
Example 3:

Input: n = 7

Output: 0

Explanation:

reverse(7) = 7.
Thus, the answer is abs(7 - 7) = 0.
 

Constraints:

1 <= n <= 10^9
*/

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// Approach: String Manipulation
int mirrorDistance(int n) {
    string s = to_string(n);
    reverse(s.begin(), s.end());
    int rev = stoi(s);
    return abs(n - rev);
}

// Approach 2: Mathematical Approach
int mirrorDistance(int n) {
    int rev = 0;
    int temp = n;
    
    while (temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    return abs(n - rev);
}

int main() {
    int n1 = 25;
    cout << "Mirror Distance of " << n1 << " is: " << mirrorDistance(n1) << endl;

    int n2 = 10;
    cout << "Mirror Distance of " << n2 << " is: " << mirrorDistance(n2) << endl;

    int n3 = 7;
    cout << "Mirror Distance of " << n3 << " is: " << mirrorDistance(n3) << endl;

    return 0;
}