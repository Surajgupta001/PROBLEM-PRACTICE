/*
Number of Arithmetic Triplets - [Leetcode - 2367(Easy)]
========================================================
You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:

i < j < k,
nums[j] - nums[i] == diff, and
nums[k] - nums[j] == diff.
Return the number of unique arithmetic triplets. 

Example 1:

Input: nums = [0,1,4,6,7,10], diff = 3
Output: 2
Explanation:
(1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
(2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3. 

Example 2:

Input: nums = [4,5,6,7,8,9], diff = 2
Output: 2
Explanation:
(0, 2, 4) is an arithmetic triplet because both 8 - 6 == 2 and 6 - 4 == 2.
(1, 3, 5) is an arithmetic triplet because both 9 - 7 == 2 and 7 - 5 == 2.
 

Constraints:

3 <= nums.length <= 200
0 <= nums[i] <= 200
1 <= diff <= 50
nums is strictly increasing.
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Brute Force O(n^3) solution
int arithmeticTriplets(vector<int>& nums, int diff) {
    int count = 0;
    int n = nums.size();
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                if(nums[j] - nums[i] == diff and nums[k] - nums[j] == diff){
                    count++;
                }
            }
        }
    }
    return count;
}

// Optimized O(n) solution
int arithmeticTriplets(vector<int>& nums, int diff){
    int count = 0;
    unordered_set<int> set;
    for(int i=0; i<nums.size(); i++){
        if(set.count(nums[i] - diff) && set.count(nums[i] - 2*diff)){
            count++;
        }
        set.insert(nums[i]);
    }
    return count;
}

// Using Binary Search O(nlogn) solution ===> Efficient Approach 
bool binarySearch(vector<int> &nums, int target){
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high){
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return true;
        else if (nums[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

int arithmeticTriplets(vector<int> &nums, int diff){
    int count = 0;
    for (int i = 0; i < nums.size(); i++){
        if (binarySearch(nums, nums[i] + diff) && binarySearch(nums, nums[i] + (2 * diff))){
            count++;
        }
    }
    return count;
}

int main(){
        
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums = {0,1,4,6,7,10};
    int diff = 3;
    cout << arithmeticTriplets(nums, diff) << endl; // Output: 2
        
    return 0;
}