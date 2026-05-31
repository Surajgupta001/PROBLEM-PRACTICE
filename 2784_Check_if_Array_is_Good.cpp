/*
Check if Array is Good - [Leetcode - 2784(Easy)]
---------------------------------------------------

You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].

base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].

Return true if the given array is good, otherwise return false.

Note: A permutation of integers represents an arrangement of these numbers.

Example 1:

Input: nums = [2, 1, 3]
Output: false
Explanation: Since the maximum element of the array is 3, the only candidate n for which this array could be a permutation of base[n], is n = 3. However, base[3] has four elements but array nums has three. Therefore, it can not be a permutation of base[3] = [1, 2, 3, 3]. So the answer is false.

Example 2:

Input: nums = [1, 3, 3, 2]
Output: true
Explanation: Since the maximum element of the array is 3, the only candidate n for which this array could be a permutation of base[n], is n = 3. It can be seen that nums is a permutation of base[3] = [1, 2, 3, 3] (by swapping the second and fourth elements in nums, we reach base[3]). Therefore, the answer is true.

Example 3:

Input: nums = [1, 1]
Output: true
Explanation: Since the maximum element of the array is 1, the only candidate n for which this array could be a permutation of base[n], is n = 1. It can be seen that nums is a permutation of base[1] = [1, 1]. Therefore, the answer is true.

Example 4:

Input: nums = [3, 4, 4, 1, 2, 1]
Output: false
Explanation: Since the maximum element of the array is 4, the only candidate n for which this array could be a permutation of base[n], is n = 4. However, base[4] has five elements but array nums has six. Therefore, it can not be a permutation of base[4] = [1, 2, 3, 4, 4]. So the answer is false.
 

Constraints:

1 <= nums.length <= 100
1 <= num[i] <= 200
*/

// NOTE: base[n] has n + 1 elements, so the length of nums should be n + 1. Also, the maximum element in nums should be n, and all elements from 1 to n - 1 should be present exactly once.
// i.e. [1, 2, 3, 4, 5, ....., n - 1, n, n] (length = n + 1)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Approach-1 (Using frequency count)
//T.C : O(n) 
//S.C : O(n)
bool isGood(vector<int>& nums) {
    int maxElement = *max_element(begin(nums), end(nums));
    
    if(nums.size() != maxElement+1){
        return false;
    }
    
    vector<int> count(maxElement+1, 0);
    
    for(int i = 0; i < nums.size(); i++) {
        count[nums[i]]++;
        
        if(nums[i] != maxElement && count[nums[i]] > 1){
            return false;
        }else if(nums[i] == maxElement && count[nums[i]] > 2){
            return false;
        }
    }
    return true;
}

//Approach-2 (Sorting)
//T.C : O(n*logn) 
//S.C : O(1)
bool isGood(vector<int>& nums) {
    int n = nums.size();
    sort(begin(nums), end(nums));

    for(int i=0; i<=n-2; i++){
        if(nums[i] != i+1){
            return false;
        }
    }
    return nums[n-1] == n-1;
}

//Approach-3 (Marking visited indices - O(1) space)
//T.C : O(n) 
//S.C : O(1)
bool isGood(vector<int>& nums) {
    int n = nums.size();

    int maxElement = n - 1;

    int maxElementCount = 0;

    for(int num : nums){
        int value = abs(num);

        if(value > maxElement){
            return false;
        }else if(value == maxElement){
            maxElementCount++;
        }

        if(nums[value] < 0){
            if(value != maxElement){
                return false;
            } else if(maxElementCount > 2){
                return false;
            }
        }else{
            nums[value] *= -1;
        }
    }
    return maxElementCount == 2;
}

int main () {
    vector<int> nums1 = {2, 1, 3};
    vector<int> nums2 = {1, 3, 3, 2};
    vector<int> nums3 = {1, 1};
    vector<int> nums4 = {3, 4, 4, 1, 2, 1};
    vector<int> nums5 = {5, 7, 3, 1, 5, 2, 6, 4};

    cout << boolalpha; // Print boolean values as true/false
    cout << "Example 1: " << isGood(nums1) << endl; // Output: false
    cout << "Example 2: " << isGood(nums2) << endl; // Output: true
    cout << "Example 3: " << isGood(nums3) << endl; // Output: true
    cout << "Example 4: " << isGood(nums4) << endl; // Output: false
    cout << "Example 5: " << isGood(nums5) << endl; // Output: false

    return 0;
}