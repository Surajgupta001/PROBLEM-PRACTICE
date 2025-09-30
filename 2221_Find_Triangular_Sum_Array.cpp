/*
Find Triangular Sum of an Array - [Leetcode - 2221(Medium)]
---------------------------------------------------------------
You are given a 0-indexed integer array nums, where nums[i] is a digit between 0 and 9 (inclusive).

The triangular sum of nums is the value of the only element present in nums after the following process terminates:

Let nums comprise of n elements. If n == 1, end the process. Otherwise, create a new 0-indexed integer array newNums of length n - 1.
For each index i, where 0 <= i < n - 1, assign the value of newNums[i] as (nums[i] + nums[i+1]) % 10, where % denotes modulo operator.
Replace the array nums with newNums.
Repeat the entire process starting from step 1.
Return the triangular sum of nums.



Example 1:

1 2 3 4 5
 3 5 7 9
  8 2 6
   0 8
    8

Input: nums = [1,2,3,4,5]
Output: 8
Explanation:
The above diagram depicts the process from which we obtain the triangular sum of the array.

Example 2:

Input: nums = [5]
Output: 5
Explanation:
Since there is only one element in nums, the triangular sum is the value of that element itself.

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 9

*/

#include <iostream>
#include <vector>
using namespace std;

// Approach - 1: Simulation
// Time Complexity: O(n^2)
// Space Complexity: O(n)
int triangularSum(vector<int> &nums) {
    vector<int> newNums;
    while (nums.size() > 1) { // O(n) iterations
        for (int i = 0; i < nums.size() - 1; i++) { // O(n) for loop
            newNums.push_back((nums[i] + nums[i + 1]) % 10);
        }
        nums = move(newNums);
    }
    return nums[0];
}

// Approach - 2: In-Place Modification
// Time Complexity: O(n^2)
// Space Complexity: O(1)
int triangularSum(vector<int> &nums) {
    int n = nums.size();
    for(int size = n; size > 1; size--) {
        for(int i = 0; i < size - 1; i++) {
            nums[i] = (nums[i] + nums[i + 1]) % 10;
        }
    }
    return nums[0];
}

// Approach - 3: Combinatorial Mathematics (Using Binomial Coefficients)
// Time Complexity: O(n)
// Space Complexity: O(1)
int triangularSum(vector<int> &nums) {
    int n = nums.size();
    int res = 0;
    long long coeff = 1;
    for (int i = 0; i < n; ++i) {
        res = (res + coeff * nums[i]) % 10;
        if (i < n - 1) {
            coeff = coeff * (n - 1 - i) / (i + 1);
        }
    }
    return (res + 10) % 10;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << "Triangular Sum: " << triangularSum(nums) << endl; // Output: 8
    return 0;
}