/*
Complement of Base 10 Integer - [Leetcode - 1009(Easy)]
---------------------------------------------------------
The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer n, return its complement.

Example 1:

Input: n = 5
Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

Example 2:

Input: n = 7
Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

Example 3:

Input: n = 10
Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.

Constraints:

0 <= n < 10^9
*/

#include <iostream>
#include <cmath>
using namespace std;

// Approach 1: Bit Manipulation
int bitwiseComplement(int n) {
    int counter = 0;
    
    int result = 0;
    if (n == 0) {
        return 1;
    }
    
    while(n) {
        int r = n % 2;
        result += pow(2, counter) * (r == 0 ? 1 : 0);
        n /= 2;
        counter++;
    }       
    return result;
}

// Approach - 2: Bit Manipulation with Mask
int bitwiseComplement(int n) {
    if (n == 0) {
        return 1;
    }

    int mask = 1;
    while (mask < n) {
        mask = (mask << 1) | 1; // Left shift the mask by 1 and set the least significant bit to 1
    }
    
    return mask ^ n;
}

// Approach - 3: Bit Manipulation with Mask (Optimized)
int bitwiseComplement(int n) {
    int bits = floor(log2(n)) + 1; // Calculate the number of bits required to represent n
    int mask = (1 << bits) - 1; // Create a mask with all bits set to 1 for the number of bits in n
    return mask ^ n; // XOR n with the mask to get the complement
}

int main () {
    int n = 5;
    cout << bitwiseComplement(n) << endl; // Output: 2

    n = 7;
    cout << bitwiseComplement(n) << endl; // Output: 0

    n = 10;
    cout << bitwiseComplement(n) << endl; // Output: 5

    return 0;
}