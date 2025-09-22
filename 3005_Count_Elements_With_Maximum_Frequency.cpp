/*
Count Elements With Maximum Frequency - [Leetcode - 3005(Easy)]
----------------------------------------------------------------
You are given an array nums consisting of positive integers.

Return the total frequencies of elements in nums such that those elements all have the maximum frequency.

The frequency of an element is the number of occurrences of that element in the array.

Example 1:

Input: nums = [1,2,2,3,1,4]
Output: 4
Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
So the number of elements in the array with maximum frequency is 4.

Example 2:

Input: nums = [1,2,3,4,5]
Output: 5
Explanation: All elements of the array have a frequency of 1 which is the maximum.
So the number of elements in the array with maximum frequency is 5.
 
Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
using namespace std;

int maxFrequencyElements(vector<int>& nums) {
    int freq[101] = {0}; // Frequency array for numbers 1 to 100
    int maxFreq = 0;    // To track the maximum frequency

    // Calculate frequencies
    for (int num : nums) {
        freq[num]++;
        maxFreq = max(maxFreq, freq[num]);
    }

    // Count elements with maximum frequency
    int count = 0;
    for (int f : freq) {
        if (f == maxFreq) {
            count += f; // Add the frequency of elements with max frequency
        }
    }

    return count;        
}

int main() {
    vector<int> nums = {1, 2, 2, 3, 1, 4};
    cout << "Total elements with maximum frequency: " << maxFrequencyElements(nums) << endl;
    return 0;
}