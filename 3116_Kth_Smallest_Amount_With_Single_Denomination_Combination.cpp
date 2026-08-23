/*
Kth Smallest Amount With Single Denomination Combination - [Leetcode - 3116(HARD)]
-------------------------------------------------------------------------------------
You are given an integer array coins representing coins of different denominations and an integer k.

You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.

Return the kth smallest amount that can be made using these coins.

Example 1:

Input: coins = [3,6,9], k = 3

Output: 9

Explanation: The given coins can make the following amounts:
Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
All of the coins combined produce: 3, 6, 9, 12, 15, etc.

Example 2:

Input: coins = [5,2], k = 7

Output: 12

Explanation: The given coins can make the following amounts:
Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
All of the coins combined produce: 2, 4, 5, 6, 8, 10, 12, 14, 15, etc.

Constraints:
1 <= coins.length <= 15
1 <= coins[i] <= 25
1 <= k <= 2 * 10^9
coins contains pairwise distinct integers.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define ll long long

//Approach (Binary Search + Inclusion Exclusion Principle)
//T.C : O(log(maxCoin * k) * 2^n * n * log(maxCoin))
//S.C : O(1)
ll countSmallerToLeft(ll mid, vector<int>& coins) { 
    ll correctedCount = 0;
    int n = coins.size();

    //2^n * n * log(maxCoin)
    for(int expressions = 1; expressions <= (1 << n) - 1; expressions++) { //2^n-1 expressions
        ll lcm = 0;
        ll order = 0; //even or odd order of expressions
        
        for(int i = 0; i < n; i++) {
            if(expressions & (1 << i)) {
                order++; //we have taken ith coin
                if(lcm == 0) {
                    lcm = coins[i];
                } else {
                    lcm = lcm * coins[i] / gcd(lcm, coins[i]);
                }
            }
        }
        if(order % 2 == 0) { //even then subtract
            correctedCount -= mid/lcm;
        } else {
            correctedCount += mid/lcm;
        }
    }
    return correctedCount;
}

long long findKthSmallest(vector<int>& coins, int k) {
    ll result = -1;
    
    ll l = 1;
    ll r = (ll)(*max_element(begin(coins), end(coins))) * k;
    
    //log(maxCoin * k) * 2^n * n * log(maxCoin)
    while(l <= r) {
        ll mid = l + (r-l)/2;
        
        if(countSmallerToLeft(mid, coins) >= k) { //left side me we can find kth smallest element
            result = mid;
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return result;
}

int main() {
    vector<int> coins = {3, 6, 9};
    int k = 3;
    cout << findKthSmallest(coins, k) << endl; // Output: 9

    coins = {5, 2};
    k = 7;
    cout << findKthSmallest(coins, k) << endl; // Output: 12

    return 0;
}