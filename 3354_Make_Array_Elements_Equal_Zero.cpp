/*
Make Array Elements Equal to Zero - [Leetcode - 3354(Easy)]
------------------------------------------------------------
You are given an integer array nums.

Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement direction of either left or right.

After that, you repeat the following process:

If curr is out of the range [0, n - 1], this process ends.
If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right, or decrementing curr if you are moving left.
Else if nums[curr] > 0:
Decrement nums[curr] by 1.
Reverse your movement direction (left becomes right and vice versa).
Take a step in your new direction.
A selection of the initial position curr and movement direction is considered valid if every element in nums becomes 0 by the end of the process.

Return the number of possible valid selections. 

Example 1:

Input: nums = [1,0,2,0,3]

Output: 2

Explanation:

The only possible valid selections are the following:

Choose curr = 3, and a movement direction to the left.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,0].
Choose curr = 3, and a movement direction to the right.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].
Example 2:

Input: nums = [2,3,4,0,4,1,0]

Output: 0

Explanation:

There are no possible valid selections.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
There is at least one element i where nums[i] == 0.
*/ 

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Approach-1 - (Simple simulation)
//T.C : O(n^ * m) 
//S.C : O(n)
bool isValid(vector<int>& nums, int count, int i, int direction) {
    vector<int> temp = nums;
    
    int idx = i;
    
    while (count > 0 && idx >= 0 && idx < nums.size()) {
        if (temp[idx] > 0) {
            temp[idx]--;
            direction *= -1;
            if (temp[idx] == 0) {
                count--;
            }
        }
        idx += direction;
    }
    return count == 0; //all must become 0
}

int countValidSelections(vector<int>& nums) {
    int result = 0;
    
    int count = 0; //count of nums[i] != 0
    
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        if (nums[i] != 0) {
            count++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            if (isValid(nums, count, i, -1)) {
                result++;
            }
            if (isValid(nums, count, i, 1)) {
                result++;
            }
        }
    }
    return result;
}

//Approach-2 - (Using cumulative sum)
//T.C : O(n) 
//S.C : O(1)
int countValidSelections(vector<int>& nums) {
    int n = nums.size();
    
    int result =0;
    int curr = 0;
    
    int S = accumulate(begin(nums), end(nums), 0);//for loop bhi likh sakte ho
    
    for(int i = 0; i < n; i++) {
        curr += nums[i]; //left sum
        
        int left  = curr;
        int right = S - left;
        
        if(nums[i] != 0) continue;
        
        if(left == right) result += 2;
        
        if(abs(left - right) == 1) result += 1;
    }
    return result;
}

int main() {
    vector<int> nums = {1,0,2,0,3};
    cout << countValidSelections(nums) << endl; // Output: 2
    return 0;
}