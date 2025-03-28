/*
Closest Prime Numbers in Range - [Leetcode - 2523(Medium)]
==========================================================
Given two positive integers left and right, find the two integers num1 and num2 such that:

left <= num1 < num2 <= right .
Both num1 and num2 are prime numbers.
num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

Example 1:

Input: left = 10, right = 19
Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Example 2:

Input: left = 4, right = 6
Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.
 

Constraints:

1 <= left <= right <= 106
*/ 

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> closestPrimes(int left, int right) {
    vector<int> primes;
    vector<bool> isPrime(right + 1, true);
    isPrime[0] = isPrime[1] = false;

    // Create a sieve [O(n log log n)]
    for (int i = 2; i * i <= right; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= right; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Find prime numbers in the range
    for (int i = left; i <= right; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    // If there are fewer than 2 primes, return [-1, -1]
    if (primes.size() < 2) {
        return {-1, -1};
    }

    // Find the closest pair [O(m)]
    long long minDiff = LLONG_MAX; // Use long long to avoid overflow
    vector<int> closestPair = {-1, -1};
    for (int i = 0; i < primes.size() - 1; i++) {
        long long diff = (long long)primes[i + 1] - primes[i]; // Cast to long long
        if (diff < minDiff) {
            minDiff = diff;
            closestPair = {primes[i], primes[i + 1]};
        }
    }
    return closestPair;
}

int main() {
    
    int left, right;
    cout << "Enter left and right values: ";
    cin >> left >> right;

    vector<int> result = closestPrimes(left, right);
    
    cout << "Closest pair of primes: " << result[0] << " " << result[1] << endl;

    return 0;
}