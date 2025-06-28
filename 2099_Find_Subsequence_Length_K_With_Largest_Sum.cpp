/*
Find Subsequence of Length K With the Largest Sum - [Leetcode - 2099(Easy)]
----------------------------------------------------------------------------
You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.



Example 1:

Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation:
The subsequence has the largest sum of 3 + 3 = 6.
Example 2:

Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation:
The subsequence has the largest sum of -1 + 3 + 4 = 6.
Example 3:

Input: nums = [3,4,3,3], k = 2
Output: [3,4]
Explanation:
The subsequence has the largest sum of 3 + 4 = 7.
Another possible subsequence is [4, 3].


Constraints:

1 <= nums.length <= 1000
-105 <= nums[i] <= 105
1 <= k <= nums.length
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Approach-1 (Using sorting with indices)
//T.C : O(nlogn)
//S.C : O(1)
vector<int> maxSubsequence(vector<int> &nums, int k){
    int n = nums.size();
    if (k == n) return nums;
    
    vector<pair<int, int>> vec(n);
    
    for (int i = 0; i < n; i++){
        vec[i] = make_pair(i, nums[i]);
    }

    auto lambda = [](auto &p1, auto &p2){
        return p1.second > p2.second;
    };
    
    sort(begin(vec), end(vec), lambda);
    sort(begin(vec), begin(vec) + k);
    
    
    vector<int> result;
    for (int i = 0; i < k; i++){
        result.push_back(vec[i].second);
    }
    
    return result;
}

//Approach-2 (Using nth_element for partial sort)
//T.C : Average O(n+k)
//S.C : O(1)
vector<int> maxSubsequence(vector<int>& nums, int k) {
    if (k == nums.size()) return nums;
    // Copy nums to a temp vector to find k largest elements
    vector<int> temp(nums);
    
    // Use nth_element to put the k largest elements in the first k positions (unordered)
    nth_element(begin(temp), begin(temp) + k - 1, end(temp), greater<int>()); //Average TC is O(n)
    
    // Determine the threshold value (k-th largest element)
    int threshold = temp[k - 1];
    
    // Count how many times threshold appears in top k elements
    int countThreshold = count(temp.begin(), temp.begin() + k, threshold); //O(k)
    
    vector<int> result;
    for (int num : nums) {
        if (num > threshold) {
            result.push_back(num);
        } else if (num == threshold && countThreshold > 0) {
            result.push_back(num);
            --countThreshold;
        }
        if (result.size() == k) break;
    }
    return result;
}