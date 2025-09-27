/*
Valid Triangle Number - [Leetcode - 611]
-----------------------------------------
Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:

Input: nums = [2,2,3,4]
Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Example 2:

Input: nums = [4,2,3,4]
Output: 4
 

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Brute Force
// Time Complexity: O(n^3)
int triangleNumber(vector<int>& nums) {
    if(nums.size() < 3) return 0;
    
    int count = 0;
    
    for(int i = 0; i < nums.size(); i++) {
        for(int j = i + 1; j < nums.size(); j++) {
            for(int k = j + 1; k < nums.size(); k++) {
                if(nums[i] + nums[j] > nums[k] && 
                   nums[i] + nums[k] > nums[j] && 
                   nums[j] + nums[k] > nums[i]) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Approach 2: Sorting + Binary Search
// Time Complexity: O(n^2*logn)
int binary_search(const vector<int>& nums, int low, int high, int target) {
    int thirdSide = -1;
    
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] < target) {
            thirdSide = mid; // Update thirdSide to the current mid - valid
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return thirdSide;
}

int triangleNumber(vector<int>& nums) {
    if(nums.size() < 3) return 0;

    sort(nums.begin(), nums.end());

    int count = 0;

    // Binary Search
    for(int i=0; i<nums.size(); i++){
        if(nums[i] == 0) continue; // Skip zero length sides
        for(int j=i+1; j<nums.size(); j++){
            int sum = nums[i] + nums[j];
            int thirdSide = binary_search(nums, j+1, nums.size()-1, sum);
            if(thirdSide != -1){
                count += (thirdSide - j); // Count valid third sides
            }
        }
    }

    return count;
}

// Approach 3: Sorting + Two Pointers
// Time Complexity: O(n^2)
int triangleNumber(vector<int>& nums) {
    if(nums.size() < 3) return 0;

    sort(nums.begin(), nums.end());

    int count = 0;

    for(int k=nums.size()-1; k>=2; k--){
        int i = 0;
        int j = k - 1;

        // nums[i] + nums[j] > nums[k]
        while(i < j){
            if(nums[i] + nums[j] > nums[k]){
                count += (j - i); // All elements between i and j can form a triangle with nums[k]
                j--; // Move the right pointer to find more combinations
            }
            else{
                i++; // Move the left pointer to increase the sum
            }
        }
    }
    
    return count;        
}

int main() {
    vector<int> nums = {2, 2, 3, 4};
    cout << "Number of valid triangles: " << triangleNumber(nums) << endl;
    return 0;
}