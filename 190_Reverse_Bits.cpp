/*
Reverse Bits - [Leetcode - 190(Easy)]
-----------------------------------------
Reverse bits of a given 32 bits signed integer.

Example 1:

Input: n = 43261596

Output: 964176192

Explanation:

Integer	Binary
43261596	00000010100101000001111010011100
964176192	00111001011110000010100101000000

Example 2:

Input: n = 2147483644

Output: 1073741822

Explanation:

Integer	Binary
2147483644	01111111111111111111111111111100
1073741822	00111111111111111111111111111110

Constraints:

0 <= n <= 2^31 - 2
n is even.

Follow up: If this function is called many times, how would you optimize it?
*/ 

#include <iostream>
using namespace std;

// Time Complexity: O(1) - The loop runs a fixed number of times (32 iterations).
int reverseBits(int n) {
    int ans = 0;
    for(int i=0; i<32; i++){
        ans = ans*2 + n%2;
        n = n/2;
    }
    return ans;       
}

// Cpp STL Solution
int reverseBits(int n) {
    unsigned int ans = 0;
    for(int i=0; i<32; i++){
        ans <<= 1; // Shift left by 1 to make room for the next bit
        ans |= (n & 1); // Add the least significant bit of n to ans
        n >>= 1; // Shift n right by 1 to process the next bit
    }
    return ans;       
}

int main() {
    int n = 43261596;
    cout << reverseBits(n) << endl; // Output: 964176192
    return 0;
}