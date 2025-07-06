/*
1865. Finding Pairs With a Certain Sum - [Leetcode - 1865(Medium)]
-------------------------------------------------------------------
You are given two integer arrays nums1 and nums2. You are tasked to implement a data structure that supports queries of two types:

Add a positive integer to an element of a given index in the array nums2.
Count the number of pairs (i, j) such that nums1[i] + nums2[j] equals a given value (0 <= i < nums1.length and 0 <= j < nums2.length).
Implement the FindSumPairs class:

FindSumPairs(int[] nums1, int[] nums2) Initializes the FindSumPairs object with two integer arrays nums1 and nums2.
void add(int index, int val) Adds val to nums2[index], i.e., apply nums2[index] += val.
int count(int tot) Returns the number of pairs (i, j) such that nums1[i] + nums2[j] == tot.
 

Example 1:

Input
["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
[[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
Output
[null, 8, null, 2, 1, null, null, 11]

Explanation
FindSumPairs findSumPairs = new FindSumPairs([1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]);
findSumPairs.count(7);  // return 8; pairs (2,2), (3,2), (4,2), (2,4), (3,4), (4,4) make 2 + 5 and pairs (5,1), (5,5) make 3 + 4
findSumPairs.add(3, 2); // now nums2 = [1,4,5,4,5,4]
findSumPairs.count(8);  // return 2; pairs (5,2), (5,4) make 3 + 5
findSumPairs.count(4);  // return 1; pair (5,0) makes 3 + 1
findSumPairs.add(0, 1); // now nums2 = [2,4,5,4,5,4]
findSumPairs.add(1, 1); // now nums2 = [2,5,5,4,5,4]
findSumPairs.count(7);  // return 11; pairs (2,1), (2,2), (2,4), (3,1), (3,2), (3,4), (4,1), (4,2), (4,4) make 2 + 5 and pairs (5,3), (5,5) make 3 + 4
 

Constraints:

1 <= nums1.length <= 1000
1 <= nums2.length <= 105
1 <= nums1[i] <= 109
1 <= nums2[i] <= 105
0 <= index < nums2.length
1 <= val <= 105
1 <= tot <= 109
At most 1000 calls are made to add and count each.

*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class FindSumPairs {
private:
    vector<int> vec1, vec2; // Store the first and second arrays
    unordered_map<int, int> freqMap; // Map to store the frequency of elements in vec2

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        vec1 = nums1; // Initialize vec1 with nums1
        vec2 = nums2; // Initialize vec2 with nums2
        for (int num : vec2) { // Populate the frequency map with elements from vec2
            freqMap[num]++;
        }
    }

    void add(int index, int value) {
        freqMap[vec2[index]]--; // Decrease the frequency of the old value
        vec2[index] += value; // Update the value at the index
        freqMap[vec2[index]]++; // Increase the frequency of the new value
    }

    int count(int total) {
        int count = 0; // Initialize count of pairs to 0
        for (int num : vec1) { // Iterate through each element in vec1
            count += freqMap[total - num]; // For each num in vec1, find how many times (total - num) appears in vec2
        }
        return count;
    }
};

int main() {
    vector<int> nums1 = {1, 1, 2, 2, 2, 3};
    vector<int> nums2 = {1, 4, 5, 2, 5, 4};
    FindSumPairs findSumPairs(nums1, nums2);

    cout << findSumPairs.count(7) << endl; // Output: 8
    findSumPairs.add(3, 2);
    cout << findSumPairs.count(8) << endl; // Output: 2
    cout << findSumPairs.count(4) << endl; // Output: 1
    findSumPairs.add(0, 1);
    findSumPairs.add(1, 1);
    cout << findSumPairs.count(7) << endl; // Output: 11

    return 0;
}