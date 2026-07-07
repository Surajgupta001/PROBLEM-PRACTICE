/*
Concatenate Non-Zero Digits and Multiply by Sum I - [Leetcode - 3754(Easy)]
-------------------------------------------------------------------------------

You are given an integer n.

Form a new integer x by concatenating all the non-zero digits of n in their original order. If there are no non-zero digits, x = 0.

Let sum be the sum of digits in x.

Return an integer representing the value of x * sum.

Example 1:

Input: n = 10203004

Output: 12340

Explanation:

The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
Therefore, the answer is x * sum = 1234 * 10 = 12340.

Example 2:

Input: n = 1000

Output: 1

Explanation:

The non-zero digit is 1, so x = 1 and sum = 1.
Therefore, the answer is x * sum = 1 * 1 = 1.

Constraints:

0 <= n <= 10^9
*/

#include <iostream>
using namespace std;

long long sumAndMultiply(int n) {
    long long x = 0; // To store the concatenated non-zero digits
    int sum = 0; // To store the sum of non-zero digits

    while (n > 0) {
        int digit = n % 10; // Get the last digit
        if (digit != 0) {
            x = digit + x * 10; // Concatenate the digit to x
            sum += digit; // Add the digit to sum
        }
        n /= 10; // Remove the last digit from n
    }

    return x * sum; // Return the product of x and sum
}

int main() {
    int n = 10203004;
    cout << sumAndMultiply(n) << endl; // Output: 12340

    n = 1000;
    cout << sumAndMultiply(n) << endl; // Output: 1

    return 0;
}