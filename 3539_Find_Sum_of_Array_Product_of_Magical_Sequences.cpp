/*
Find Sum of Array Product of Magical Sequences - [Leetcode - 2539(Hard)]
--------------------------------------------------------------------------
You are given two integers, m and k, and an integer array nums.

A sequence of integers seq is called magical if:
=> seq has a size of m.
=> 0 <= seq[i] < nums.length
=> The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
=> The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).

Return the sum of the array products for all valid magical sequences.

Since the answer may be large, return it modulo 109 + 7.

A set bit refers to a bit in the binary representation of a number that has a value of 1.

 

Example 1:

Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]

Output: 991600007

Explanation:

All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.

Example 2:

Input: m = 2, k = 2, nums = [5,4,3,2,1]

Output: 170

Explanation:

The magical sequences are [0, 1], [0, 2], [0, 3], [0, 4], [1, 0], [1, 2], [1, 3], [1, 4], [2, 0], [2, 1], [2, 3], [2, 4], [3, 0], [3, 1], [3, 2], [3, 4], [4, 0], [4, 1], [4, 2], and [4, 3].

Example 3:

Input: m = 1, k = 1, nums = [28]

Output: 28

Explanation:

The only magical sequence is [0].
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

#define ll long long
int mod = 1e9 + 7;

// Here we use memoization to optimize the recursive calls but it is still not efficient enough for larger inputs. Because the value of m does not given, so how many takes we can have is unknown. And also the sum can be very large as well.
// So here we use unordered_map to store count and sum as a key pair and the result as value pair.

//Approach-1 (Recursion + Memoization with Brute Force)
//T.C : O(m*N) after memoization but sum value becomes extremely high - Not feasible
//S.C : O(M*2^N)
unordered_map<string, int> mp;
ll helper(int count, ll sum, vector<int>& nums, int m, int k) {
    int n = nums.size();
    if(count == m) {
        return (__builtin_popcountll(sum) == k) ? 1 : 0;
    }
    string key = to_string(count) + "_" + to_string(sum);
    if(mp.count(key)) {
        return mp[key];
    }
    ll totalSum = 0;
    for(int i = 0; i < n; i++) {
        ll newSum = sum + (1LL << i);
        ll prod = (nums[i] * helper(count+1, newSum, nums, m, k)) % mod;
        totalSum = (totalSum + prod) % mod;
    }
    return mp[key] = totalSum;
}

int magicalSum(int m, int k, vector<int>& nums) {
    int n = nums.size();
    return (int)(helper(0, 0, nums, m, k) % mod);
}

//Approach-2 : Usin Recursion + Memo with Bit Memoization (Digit DP)
//T.C : O(N* M^2 * K)
//S.C : O(N*M*K)
map<tuple<ll, int , int, int>, ll> dp;
vector<ll> fact;
vector<ll> invFact;

ll findPower(ll a, ll b) {
    if(b == 0) return 1;
    
    ll half = findPower(a, b/2);
    ll result = (half * half) % mod;
    
    if(b%2 == 1) result = (result * a) % mod;

    return result;
}

//nCr % mod
ll nCr(int n, int r) {
    //nCr = n! * inv(n-r)! * inv(r)!
    return (((fact[n] * invFact[r]) % mod) * invFact[n-r]) % mod;
}

// Recursive function to calculate the sum of products of magical sequences
ll helper(ll binarySum, int m, int k, int i, vector<int>& nums) {
    int n = nums.size();
    auto key = make_tuple(binarySum, m, k, i);
    
    if(dp.count(key)) return dp[key];
    if(m == 0 && __builtin_popcount(binarySum) == k) return 1;
    if(m == 0 || i >= n) return 0;
    
    ll totalSum = 0;
    
    //Skip index i
    totalSum = (totalSum + helper((binarySum >> 1), m, k - (binarySum & 1), i+1, nums)) % mod;
    
    //Take index i freq number of times
    for(int freq = 1; freq <= m; freq++) {
        ll newBinarySum = binarySum + freq;
        
        int carry = newBinarySum >> 1;
        
        ll prod = helper((carry), m - freq, k - (newBinarySum & 1), i+1, nums);
        
        prod = (findPower(nums[i], freq) % mod * prod % mod) % mod;
        
        prod = (prod * nCr(m, freq)) % mod;
        
        totalSum = (totalSum + prod) % mod;
    }

    return dp[key] = totalSum;
}

int magicalSum(int m, int k, vector<int>& nums) {
    int n = nums.size();
    
    //Precompute factoriala and inverse factorials
    fact.assign(m+1, 1);
    invFact.assign(m+1, 1);
    
    for(int i = 2; i <= m; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    //Fermat's little theorem for inverse factorials
    for(int i = 0; i <= m; i++) {
        invFact[i] = findPower(fact[i], mod-2);
    }
    
    return (int)(helper(0, m, k, 0, nums) % mod);
}

int main() {
    int m = 5, k = 5;
    vector<int> nums = {1,10,100,10000,1000000};

    cout << magicalSum(m, k, nums) << endl;

    return 0;
}