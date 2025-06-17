/*
Count the Number of Arrays with K Matching Adjacent Elements - [Leetcode - 3405(Hard)]
---------------------------------------------------------------------------------------
You are given three integers n, m, k. A good array arr of size n is defined as follows:

Each element in arr is in the inclusive range [1, m].
Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].
Return the number of good arrays that can be formed.

Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:

Input: n = 3, m = 2, k = 1

Output: 4

Explanation:

There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
Hence, the answer is 4.
Example 2:

Input: n = 4, m = 2, k = 2

Output: 6

Explanation:

The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].
Hence, the answer is 6.
Example 3:

Input: n = 5, m = 2, k = 0

Output: 2

Explanation:

The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the answer is 2.
 

Constraints:

1 <= n <= 10^5
1 <= m <= 10^5
0 <= k <= n - 1
*/ 

#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9 + 7;

long long findPower(long long base, long long exp) {
    if (exp == 0) return 1;
    long long half = findPower(base, exp / 2);
    long long result = (half * half) % mod;
    if (exp % 2 == 1) {
        result = (result * base) % mod;
    }
    return result;
}

long long nCr(int n, int r, vector<long long> &factorial, vector<long long> &inverseFactorial) {
    // n!/(r! * (n - r)!) % mod
    return factorial[n] * inverseFactorial[r] % mod * inverseFactorial[n - r] % mod; // O(1)
}

int countGoodArrays(int n, int m, int k) {
    vector<long long> factorial(n + 1, 1);
    factorial[0] = 1;
    factorial[1] = 1;

    // Precompute factorials up to n
    for(int i=2; i<= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod; // Precompute factorials
    }

    // Calculating Inverse factorial precalculation - Fermat's Little Theorem
    vector<long long> inverseFactorial(n + 1, 1);
    for(int i=0; i<=n; i++) {
        inverseFactorial[i] = findPower(factorial[i], mod - 2);
    }

    long long result = nCr(n - 1, k, factorial, inverseFactorial);
    result = (result * m) % mod; // Multiply by m for the first element
    result = (result * findPower(m - 1, (n - k - 1))) % mod;
    
    return result;
}

int main() {
    int n=3, m=2, k=1;

    int result = countGoodArrays(n, m, k);
    cout << result << endl;

    return 0;
}