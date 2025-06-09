/*
K-th Smallest in Lexicographical Order - [Leetcode - 440(Hard)]
----------------------------------------------------------------
Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].

Example 1:

Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.

Example 2:

Input: n = 1, k = 1
Output: 1
 

Constraints:

1 <= k <= n <= 109
*/ 

#include <iostream>
using namespace std;

/*
Time Complexity: O((log₁₀(n))²)
Space Complexity: O(1)
*/ 

int Count(long curr, long next, int n) {
    int countNum = 0;
    while(curr <= n) {
        countNum += (next - curr);

        curr *= 10; // Move to the next level in the lexicographical tree
        next *= 10; // Move to the next level in the lexicographical tree

        next = min(next, (long)n + 1); // Ensure next does not exceed n + 1
    }
    return countNum;
}

int findKthNumber(int n, int k) {
    int curr = 1; // Start with the smallest lexicographical number
    k -= 1; // Since we start from the first number (1), we need to k-1 more numbers to find the k-th one

    while(k > 0) {
        int count = Count(curr, curr+1, n);

        if(count <= k) {
            // If the count of numbers in the current range is less than or equal to k,
            // we move to the next number in lexicographical order
            curr += 1;
            k -= count; // Decrease k by the count of numbers in the current range
        } else {
            // If the count is greater than k, we go deeper into the tree
            curr *= 10; // Move to the next level in the lexicographical tree
            k -= 1; // We have used one number (curr)
        }
    }
    return curr;
}

int main() {
    int n = 13, k = 2;
    cout << "The " << k << "-th smallest number in lexicographical order from 1 to " << n << " is: " << findKthNumber(n, k) << endl;

    n = 1, k = 1;
    cout << "The " << k << "-th smallest number in lexicographical order from 1 to " << n << " is: " << findKthNumber(n, k) << endl;

    return 0;
}