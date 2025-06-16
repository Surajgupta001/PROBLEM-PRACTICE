/*
Minimize Maximum of Array - [Leetcode - 2439(Medium)]
------------------------------------------------------
You are given a 0-indexed array nums comprising of n non-negative integers.

In one operation, you must:

Choose an integer i such that 1 <= i < n and nums[i] > 0.
Decrease nums[i] by 1.
Increase nums[i - 1] by 1.
Return the minimum possible value of the maximum integer of nums after performing any number of operations.

Example 1:

Input: nums = [3,7,1,6]
Output: 5
Explanation:
One set of optimal operations is as follows:
1. Choose i = 1, and nums becomes [4,6,1,6].
2. Choose i = 3, and nums becomes [4,6,2,5].
3. Choose i = 1, and nums becomes [5,5,2,5].
The maximum integer of nums is 5. It can be shown that the maximum number cannot be less than 5.
Therefore, we return 5.

Example 2:

Input: nums = [10,1]
Output: 10
Explanation:
It is optimal to leave nums as is, and since 10 is the maximum value, we return 10.

Constraints:

n == nums.length
2 <= n <= 105
0 <= nums[i] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isValid(vector<int> &nums, int mid_max, int n){
    vector<long long> v(begin(nums), end(nums));
    for (int i = 0; i < n - 1; i++){
        if (v[i] > mid_max) return false;
        
        long long buffer = mid_max - v[i];
        v[i + 1] = v[i + 1] - buffer;
    }
    return v[n - 1] <= mid_max;
}

int minimizeArrayValue(vector<int> &nums){
    int n = nums.size();

    int low = 0;
    int high = *max_element(begin(nums), end(nums));

    int result;

    while (low <= high){

        int mid_max = low + (high - low) / 2;

        if (isValid(nums, mid_max, n)){
            result = mid_max;
            high = mid_max - 1;
        }
        else{
            low = mid_max + 1;
        }
    }

    return result;
}

// Another approach using prefix sum
int minimizeArrayValue(vector<int> &nums) {
    long long prefixSum = 0;
    int result = 0;
    for(int i=0; i<nums.size(); i++) {
        prefixSum += nums[i]; // Calculate the prefix sum
        result = max(result, (int)((prefixSum + i) / (i + 1))); // Calculate the minimum possible value
        /*
        i	   prefixSum	(prefixSum + i) / (i+1)     result
        0	   3	        (3+0)/1 = 3	                3
        1	   10	        (10+1)/2 = 5.5 -> 5	        5
        2	   11	        (11+2)/3 = 4.33 -> 4	    5
        3	   17	        (17+3)/4 = 5	            5

        The prefix sum approach efficiently finds the minimum possible maximum value by ensuring no prefix is forced to have a value larger than its average, considering the allowed operations.
        */ 
    }
    return result;
}
    

int main(){
    vector<int> nums = {3, 7, 1, 6};
    cout << "Minimum possible value of the maximum integer of nums: " << minimizeArrayValue(nums) << endl;

    nums = {10, 1};
    cout << "Minimum possible value of the maximum integer of nums: " << minimizeArrayValue(nums) << endl;

    return 0;
}