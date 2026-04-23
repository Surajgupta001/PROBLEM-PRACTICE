/*
Sum of Distances - [Leetcode - 2615(Medium)]
---------------------------------------------
You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.

Return the array arr.

Example 1:

Input: nums = [1,3,1,1,2]
Output: [5,0,3,4,0]
Explanation: 
When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
When i = 1, arr[1] = 0 because there is no other index with value 3.
When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
When i = 4, arr[4] = 0 because there is no other index with value 2. 

Example 2:

Input: nums = [0,5,3]
Output: [0,0,0]
Explanation: Since each element in nums is distinct, arr[i] = 0 for all i.
 
Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
 

Note: This question is the same as 2121: Intervals Between Identical Elements.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<long long> distance(vector<int>& nums) {
    int n = nums.size();

    vector<long long> result(n, 0); // Initialize the result array with 0s
    
    unordered_map<int, long long> indexSum; // Map to store the sum of indices for each unique value
    unordered_map<int, int> indexCount; // Map to store the count of occurrences for each unique value

    // Left to Right
    for(int i=0; i<n; i++){
        long long freq = indexCount[nums[i]];
        long long sum = indexSum[nums[i]];

        result[i] += (freq * i) - sum; // Calculate the distance contribution from the left side
        
        indexCount[nums[i]]++; // Increment the count for the current value
        indexSum[nums[i]] += i; // Add the current index to the sum for the current value
    }
    
    indexSum.clear(); // Clear the index sum map for the right to left pass
    indexCount.clear(); // Clear the index count map for the right to left pass

    // Right to Left
    for(int i=n-1; i>=0; i--){
        long long freq = indexCount[nums[i]];
        long long sum = indexSum[nums[i]];

        result[i] += sum - (freq * i); // Calculate the distance contribution from the right side
        
        indexCount[nums[i]]++; // Increment the count for the current value
        indexSum[nums[i]] += i; // Add the current index to the sum for the current value
    }

    return result; // Return the final result array
}

int main() {
    vector<int> nums = {1, 3, 1, 1, 2};
    vector<long long> result = distance(nums);

    for (long long val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}