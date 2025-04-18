/*
Count Equal and Divisible Pairs in an Array - [Leetcode - 2176(Easy)]
=====================================================================
Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i, j) where 0 <= i < j < n, such that nums[i] == nums[j] and (i * j) is divisible by k.

Example 1:

Input: nums = [3,1,2,2,2,1,3], k = 2
Output: 4
Explanation:
There are 4 pairs that meet all the requirements:
- nums[0] == nums[6], and 0 * 6 == 0, which is divisible by 2.
- nums[2] == nums[3], and 2 * 3 == 6, which is divisible by 2.
- nums[2] == nums[4], and 2 * 4 == 8, which is divisible by 2.
- nums[3] == nums[4], and 3 * 4 == 12, which is divisible by 2.
Example 2:

Input: nums = [1,2,3,4], k = 1
Output: 0
Explanation: Since no value in nums is repeated, there are no pairs (i,j) that meet all the requirements.
 

Constraints:

1 <= nums.length <= 100
1 <= nums[i], k <= 100
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <numeric> // For std::gcd
#include <algorithm>
using namespace std;

// // Brute Force Approach
// int countPairs(vector<int>& nums, int k) {
//     int n = nums.size();
//     int count = 0;
//     for(int i=0; i<n; i++){
//         for(int j=i+1; j<n; j++){
//             if(nums[i] == nums[j] && (i * j) % k == 0) count++;
//         }
//     }    
//     return count;   
// }

// Efficient Approach
int countPairs(vector<int>& nums, int k) {
    int n = nums.size();
    int result = 0;

    unordered_map<int, vector<int>> indicesMap;
    for (int i = 0; i < n; i++) {
        indicesMap[nums[i]].push_back(i);
    }

    // k = 36
    // 1, 2, 3, 4, 5, 6
    unordered_set<int> div;
    for (int f = 1; f * f <= k; f++) { // O(sqrt(k))
        if (k % f == 0) {
            div.insert(f); //{1, 2, 3, 4, 6, 36, 18, 12, 9}
            div.insert(k / f);
        }
    }

    // O(n * (log(k) + sqrt(k)))
    for (auto& [num, indices] : indicesMap) {
        unordered_map<int, int> factorsMap;

        for (int i : indices) {
            int GCD = std::gcd(i, k); // T.C : log(k)
            int j = k / GCD;

            result += factorsMap[j];

            for (int f : div) {
                if (i % f == 0) {
                    factorsMap[f]++;
                }
            }
        }
    }
    return result;
}

int main(){
       
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums = {3,1,2,2,2,1,3};
    int k = 2;
    cout << countPairs(nums, k) << endl; 
        
    return 0;
}