/*
2948. Make Lexicographically Smallest Array by Swapping Elements - [Leetcode - 2948(Medium)]
-----------------------------------------------------------------------------------------------
You are given a 0-indexed array of positive integers nums and a positive integer limit.

In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.

Return the lexicographically smallest array that can be obtained by performing the operation any number of times.

An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.

Example 1:

Input: nums = [1,5,3,9,8], limit = 2
Output: [1,3,5,8,9]
Explanation: Apply the operation 2 times:
- Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
- Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
We cannot obtain a lexicographically smaller array by applying any more operations.
Note that it may be possible to get the same result by doing different operations.

Example 2:

Input: nums = [1,7,6,18,2,1], limit = 3
Output: [1,6,7,18,1,2]
Explanation: Apply the operation 3 times:
- Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
- Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
- Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
We cannot obtain a lexicographically smaller array by applying any more operations.

Example 3:

Input: nums = [1,7,28,19,10], limit = 3
Output: [1,7,28,19,10]
Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= limit <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
using namespace std;

// Brute Force Approach
vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
    int n = nums.size();

    for(int i=0; i<n; i++){
        while(true){
            int smallValue = nums[i];
            int idx = -1;

            for(int j=i+1; j<n; j++){
                if(abs(nums[i] - nums[j]) <= limit && nums[j] < smallValue){
                    smallValue = nums[j];
                    idx = j;
                }
            }
            if(idx == -1) break;
            swap(nums[i], nums[idx]);
        }
    }
    return nums;
}

// Better Approach
vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
    int n = nums.size();

    vector<int> vec = nums;
    sort(vec.begin(), vec.end());

    int groupNum = 0;
    unordered_map<int, int> numToGroup;
    numToGroup[vec[0]] = groupNum;

    unordered_map<int, list<int>> groupToList;
    groupToList[groupNum].push_back(vec[0]);

    for(int i = 1; i < n; i++){
        if(vec[i] - vec[i-1] > limit){
            groupNum++;
        }
        numToGroup[vec[i]] = groupNum;
        groupToList[groupNum].push_back(vec[i]);
    }

    // Build the result array directly inside 'nums' to prevent out-of-bounds error
    for(int i = 0; i < n; i++){
        int num = nums[i];
        int group = numToGroup[num];
        
        // Get the smallest number from the group
        nums[i] = groupToList[group].front();
        groupToList[group].pop_front();
    }
    return nums;
}


int main() {
    vector<int> nums1 = {1, 5, 3, 9, 8};
    int limit1 = 2;
    vector<int> result1 = lexicographicallySmallestArray(nums1, limit1);
    for(int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> nums2 = {1, 7, 6, 18, 2, 1};
    int limit2 = 3;
    vector<int> result2 = lexicographicallySmallestArray(nums2, limit2);
    for(int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> nums3 = {1, 7, 28, 19, 10};
    int limit3 = 3;
    vector<int> result3 = lexicographicallySmallestArray(nums3, limit3);
    for(int num : result3) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}