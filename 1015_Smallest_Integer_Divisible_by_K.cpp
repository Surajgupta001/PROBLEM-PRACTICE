/*
Smallest Integer Divisible by K - [Leetcode - 1015(Medium)]
-------------------------------------------------------------
Given a positive integer k, you need to find the length of the smallest positive integer n such that n is divisible by k, and n only contains the digit 1.

Return the length of n. If there is no such n, return -1.

Note: n may not fit in a 64-bit signed integer.

Example 1:

Input: k = 1
Output: 1
Explanation: The smallest answer is n = 1, which has length 1.

Example 2:

Input: k = 2
Output: -1
Explanation: There is no such positive integer n divisible by 2.

Example 3:

Input: k = 3
Output: 3
Explanation: The smallest answer is n = 111, which has length 3.

Constraints:

1 <= k <= 10^5

Leetcode - 1018 => using similar approach of remainders for getting next number
*/

#include <iostream>
using namespace std;

int smallestRepunitDivByK(int k) {
    int num = 0;

    for(int length = 1; length <= k; length++){
        num = (num * 10 + 1) % k; // Remainder will never exceed k-1, hence avoiding integer overflow
        if(num == 0){
            return length;
        }
    }
    return -1;
}

int main() {
    int k = 3;
    int result = smallestRepunitDivByK(k);
    cout << "The length of the smallest integer n divisible by " << k << " is: " << result << endl;
    return 0;
}