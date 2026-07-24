/*
Number of Unique XOR Triplets II - [Leetcode - 3514(Medium)]
---------------------------------------------------------------

You are given an integer array nums.

A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.

Return the number of unique XOR triplet values from all possible triplets (i, j, k).

Example 1:

Input: nums = [1,3]

Output: 2

Explanation:

The possible XOR triplet values are:

(0, 0, 0) → 1 XOR 1 XOR 1 = 1
(0, 0, 1) → 1 XOR 1 XOR 3 = 3
(0, 1, 1) → 1 XOR 3 XOR 3 = 1
(1, 1, 1) → 3 XOR 3 XOR 3 = 3
The unique XOR values are {1, 3}. Thus, the output is 2.

Example 2:

Input: nums = [6,7,8,9]

Output: 4

Explanation:

The possible XOR triplet values are {6, 7, 8, 9}. Thus, the output is 4.

 

Constraints:

1 <= nums.length <= 1500
1 <= nums[i] <= 1500
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int uniqueXorTriplets(vector<int>& nums) {
    int n = nums.size();
    
    // Store all pair Xors
    unordered_set<int> set1;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            set1.insert(nums[i] ^ nums[j]);
        }
    }

    // Find triplets Xors
    unordered_set<int> set2;
    for(auto &pairXor : set1){
        for(auto &num : nums){
            set2.insert(pairXor ^ num);
        }
    }

    return set2.size();
}

int main() {
    vector<int> nums1 = {1, 3};
    cout << "Unique XOR Triplets Count: " << uniqueXorTriplets(nums1) << endl; // Output: 2

    vector<int> nums2 = {6, 7, 8, 9};
    cout << "Unique XOR Triplets Count: " << uniqueXorTriplets(nums2) << endl; // Output: 4

    return 0;
}