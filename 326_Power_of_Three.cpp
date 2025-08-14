/*
Power of Three - [Leetcode - 326(Easy)]
----------------------------------------
Given an integer n, return true if it is a power of three. Otherwise, return false.

An integer n is a power of three, if there exists an integer x such that n == 3x.

Example 1:

Input: n = 27
Output: true
Explanation: 27 = 33

Example 2:

Input: n = 0
Output: false
Explanation: There is no x where 3x = 0.

Example 3:

Input: n = -1
Output: false
Explanation: There is no x where 3x = (-1).
 

Constraints:

-231 <= n <= 231 - 1
 
Follow up: Could you solve it without loops/recursion?
*/

#include <iostream>
#include <cmath>
using namespace std;

// Approach - 1: Iterative
// Time Complexity: O(log n)
bool isPowerOfThree(int n) {
    if (n <= 0) return false;
    while (n % 3 == 0) n /= 3;
    return n == 1;
}

// Approach - 2: Recursion
// Time Complexity: O(log n)
bool isPowerOfThreeRec(int n) {
    if (n <= 0) return false;
    if (n == 1) return true;
    if (n % 3 != 0) return false;
    return isPowerOfThreeRec(n / 3);
}

// Approach - 3: Mathematical
// Time Complexity: O(1)
bool isPowerOfThreeMath(int n) {
    if (n <= 0) return false;
    double logResult = log10(n) / log10(3);
    return logResult == floor(logResult);
}

int main() {
    int n = 27;
    cout << isPowerOfThree(n) << endl;  // Output: 1 (true)
    return 0;
}