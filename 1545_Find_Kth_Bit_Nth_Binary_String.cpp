/*
Find Kth Bit in Nth Binary String - [Leetcode - 1545(Medium)]
-----------------------------------------------------------------
Given two positive integers n and k, the binary string Sn is formed as follows:

S1 = "0"
Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first four strings in the above sequence are:

S1 = "0"
S2 = "011"
S3 = "0111001"
S4 = "011100110110001"
Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

Example 1:

Input: n = 3, k = 1
Output: "0"
Explanation: S3 is "0111001".
The 1st bit is "0".

Example 2:

Input: n = 4, k = 11
Output: "1"
Explanation: S4 is "011100110110001".
The 11th bit is "1".

Constraints:

1 <= n <= 20
1 <= k <= 2^n - 1
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

char findKthBit(int n, int k) {
    if (n == 1) return '0'; // Base case: S1 is "0"

    int length = (1 << n) - 1; // Length of Sn is 2^n - 1 or you can also use pow(2, n) - 1

    if(k < ceil(length / 2.0)){
        return findKthBit(n - 1, k); // If k is in the first half, it's the same as the kth bit in Sn-1
    }
    else if(k == ceil(length / 2.0)){
        return '1'; // If k is exactly in the middle, it's always '1'
    }
    else{
        auto ch = findKthBit(n - 1, length - k + 1); // If k is in the second half, find the corresponding bit in Sn-1
        return (ch == '0') ? '1' : '0'; // Invert the bit found in Sn-1
    }
}

int main() {
    int n1 = 3, k1 = 1;
    cout << findKthBit(n1, k1) << endl; // Output: "0"

    int n2 = 4, k2 = 11;
    cout << findKthBit(n2, k2) << endl; // Output: "1"

    return 0;
}