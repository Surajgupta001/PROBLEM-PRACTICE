/*
Divide Array Into Equal Pairs - [Leetcode - 2206(easy)]
=========================================================
You are given an integer array nums consisting of 2 * n integers.

You need to divide nums into n pairs such that:

Each element belongs to exactly one pair.
The elements present in a pair are equal.
Return true if nums can be divided into n pairs, otherwise return false.

Example 1:

Input: nums = [3,2,3,2,2,2]
Output: true
Explanation: 
There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.

Example 2:

Input: nums = [1,2,3,4]
Output: false
Explanation: 
There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs satisfy every condition.
 
Constraints:

nums.length == 2 * n
1 <= n <= 500
1 <= nums[i] <= 500
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
========= Bit Manupulations ===========
bool divideArray(vector<int>& nums){
    int n = nums.size()/2;
    int mask = 0;

    // Iterating over the array and upadting the bit mask
    for(int i = 0; i < nums.size(); i++){
        // Creating a bit mask for the current number
        int bitMask = 1 << nums[i];

        // If the bit mask is already set, it means we have found a pair
        if((mask & bitMask)){
            // Clear the bit
            mask ^= bitMask;
        }
        else{
            // Set the bit
            mask |= bitMask;
        }
    }
    // If the bit mask is zero/cleared, it means we have found a pair for each number
    return mask == 0;
}
*/ 

bool divideArray(vector<int>& nums){
    unordered_map<int, int> countMap;
    for (int num : nums){
        countMap[num]++;
    }
    for (auto& pair : countMap){
        if (pair.second % 2 != 0){
            return false;
        }
    }
    return true;
}

int main(){
    vector<int> nums = {3,2,3,2,2,2};
    cout << boolalpha << divideArray(nums) << endl;
    return 0;
}