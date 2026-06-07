/*
Left and Right Sum Differences - [Leetcode - 2574(Easy)]
-------------------------------------------------------------
You are given a 0-indexed integer array nums of size n.

Define two arrays leftSum and rightSum where:

leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.

Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

Example 1:

Input: nums = [10,4,8,3]
Output: [15,1,11,22]
Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].

Example 2:

Input: nums = [1]
Output: [0]
Explanation: The array leftSum is [0] and the array rightSum is [0].
The array answer is [|0 - 0|] = [0].
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> leftRightDifference(vector<int>& nums) {
    int n = nums.size();
    
    int sum = accumulate(nums.begin(), nums.end(), 0);

    vector<int> answer(n);

    int curr = 0;

    for(int i=0; i<n; i++){
        int leftSum = curr;

        curr += nums[i];

        int rightSum = sum - curr;

        answer[i] = abs(leftSum - rightSum);
    }

    return answer;
}

int main() {
    vector<int> nums1 = {10, 4, 8, 3};
    vector<int> result1 = leftRightDifference(nums1);
    cout << "Output for Example 1: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> nums2 = {1};
    vector<int> result2 = leftRightDifference(nums2);
    cout << "Output for Example 2: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}