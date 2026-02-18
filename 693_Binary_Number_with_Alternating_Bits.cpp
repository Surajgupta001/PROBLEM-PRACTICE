/*
Binary Number with Alternating Bits - [Leetcode - 693(Easy)]
--------------------------------------------------------------
Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

Example 1:

Input: n = 5
Output: true
Explanation: The binary representation of 5 is: 101

Example 2:

Input: n = 7
Output: false
Explanation: The binary representation of 7 is: 111.

Example 3:

Input: n = 11
Output: false
Explanation: The binary representation of 11 is: 1011.
 
Constraints:

1 <= n <= 2^31 - 1
*/

#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

//Approach-1 (Using shift operators and Xor operation)
//T.C : O(log(n))
//S.C : O(1)
bool hasAlternatingBits(int n) {
    bitset<32> b(n);
    int bits = log2(n);
    for(int i = 0; i<=bits; i++) {
        if(b[i] == b[i+1]) return false;
    }
    return true;
}


//Approach-2 (Using shift operators and Xor op               meration)
//T.C : O(log(n))
//S.C : O(1)
bool hasAlternatingBits(int n) {
    int currBit = n % 2;
    n /= 2;
    while (n > 0) {
        if (currBit == n % 2) 
            return false;
        
        currBit = n % 2;
        n /= 2;
    }
    
    return true;
}


//Approach-3 (Using shift operators and Xor operation)
//T.C : O(1)
//S.C : O(1)
bool hasAlternatingBits(int n) {
    unsigned int result = n ^ (n >> 1);
    return (result & (result + 1)) == 0;
}

int main () {
    int n = 5;
    
    cout << hasAlternatingBits(n) << endl; // Output: true

    n = 7;
    cout << hasAlternatingBits(n) << endl; // Output: false

    n = 11;
    cout << hasAlternatingBits(n) << endl; // Output: false

    return 0;
}