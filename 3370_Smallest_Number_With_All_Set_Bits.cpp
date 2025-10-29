/*
Smallest Number With All Set Bits - [Leetcode - 3370(Easy)]
------------------------------------------------------------
You are given a positive number n.

Return the smallest number x greater than or equal to n, such that the binary representation of x contains only set bits

Example 1:

Input: n = 5

Output: 7

Explanation:

The binary representation of 7 is "111".

Example 2:

Input: n = 10

Output: 15

Explanation:

The binary representation of 15 is "1111".

Example 3:

Input: n = 3

Output: 3

Explanation:

The binary representation of 3 is "11".

Constraints:

1 <= n <= 1000
*/ 

// NOTE : ========== 2^k - 1 => all set bit wala number aa jaiga ==========

#include <iostream>
#include <cmath>
using namespace std;

// Approach - 1: 
bool isAllBitsSet(int n){
    return (n & (n+1)) == 0;
}

int smallestNumber(int n){
    int result = n;
    
    while(!isAllBitsSet(result)){
        result ++;
    }
    return result;
}

// Approach - 2:
int smallestNumber(int n){
    int result = 1;
    
    while(result < n){
        result = 2 * result + 1;
    }

    return result;
}

// Approach - 3:
int smallestNumber(int n) {
    int bits = log2(n) + 1; // number of bits required to represent n

    return (1 << bits) - 1; // 2^bits - 1
}

int main() {
    int n = 10;
    cout << smallestNumber(n) << endl; // Output: 15
}