/*
Concatenation of Consecutive Binary Numbers - [Leetcode - 1680(Medium)]
---------------------------------------------------------------------------
Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.

Example 1:

Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 

Example 2:

Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.

Example 3:

Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.

Constraints:

1 <= n <= 10^5
*/

#include <iostream>
#include <cmath>
using namespace std;

int concatenatedBinary(int n) {
    long long result = 0;
    int mod = 1e9 + 7;

    for(int num = 1; num <= n; num++){
        int digit = log2(num) + 1; // calculate the number of bits required to represent num in binary
        result = ((result << digit) + num) % mod; // left shift the result by the number of bits and add the current number, then take modulo
    }
    return result;
}

int main(){
    int n = 12;
    cout << concatenatedBinary(n) << endl; // Output: 505379714
    return 0;
}