/*
Number of Perfect Pairs - [Leetcode - 3649(Medium)]
-----------------------------------------------------
You are given an integer array nums.

A pair of indices (i, j) is called perfect if the following conditions are satisfied:

=> i < j
=> Let a = nums[i], b = nums[j]. Then:
=> min(|a - b|, |a + b|) <= min(|a|, |b|)
=> max(|a - b|, |a + b|) >= max(|a|, |b|)

Return the number of distinct perfect pairs.

Note: The absolute value |x| refers to the non-negative value of x.

Example 1:

Input: nums = [0,1,2,3]

Output: 2

Explanation:

There are 2 perfect pairs:

(i, j)	(a, b)	min(|a − b|, |a + b|)	min(|a|, |b|)	max(|a − b|, |a + b|)	max(|a|, |b|)
(1, 2)	(1, 2)	min(|1 − 2|, |1 + 2|) = 1	1	max(|1 − 2|, |1 + 2|) = 3	2
(2, 3)	(2, 3)	min(|2 − 3|, |2 + 3|) = 1	2	max(|2 − 3|, |2 + 3|) = 5	3

Example 2:

Input: nums = [-3,2,-1,4]

Output: 4

Explanation:

There are 4 perfect pairs:

(i, j)	(a, b)	min(|a − b|, |a + b|)	min(|a|, |b|)	max(|a − b|, |a + b|)	max(|a|, |b|)
(0, 1)	(-3, 2)	min(|-3 - 2|, |-3 + 2|) = 1	2	max(|-3 - 2|, |-3 + 2|) = 5	3
(0, 3)	(-3, 4)	min(|-3 - 4|, |-3 + 4|) = 1	3	max(|-3 - 4|, |-3 + 4|) = 7	4
(1, 2)	(2, -1)	min(|2 - (-1)|, |2 + (-1)|) = 1	1	max(|2 - (-1)|, |2 + (-1)|) = 3	2
(1, 3)	(2, 4)	min(|2 - 4|, |2 + 4|) = 2	2	max(|2 - 4|, |2 + 4|) = 6	4

Example 3:

Input: nums = [1,10,100,1000]

Output: 0

Explanation:

There are no perfect pairs. Thus, the answer is 0.

Constraints:

2 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long perfectPairs(vector<int>& nums) {
    int n = (int)nums.size(); // Get the size of the input array
    vector<long long> a(n); // Create a vector to store absolute values
    for (int i = 0; i < n; ++i) {
        long long x = nums[i];
        if (x < 0) x = -x; // absolute value as 64-bit
        a[i] = x;
    }
    sort(a.begin(), a.end());

    long long ans = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        while (l < r && a[r] > 2 * a[l]) ++l;
        ans += (r - l);  // count
    }
    return ans;
}

int main() {
    vector<int> nums = {0, 1, 2, 3};
    cout << perfectPairs(nums) << endl; // Output: 2

    nums = {-3, 2, -1, 4};
    cout << perfectPairs(nums) << endl; // Output: 4

    nums = {1, 10, 100, 1000};
    cout << perfectPairs(nums) << endl; // Output: 0

    return 0;
}

// Steps

// Take absolute values and sort.
// Two-pointer sweep: for each right index r, find the smallest l such that abs[r] <= 2*abs[l], then add (r - l) to the answer.
// Zeros only pair with zeros; the two-pointer method handles this naturally.