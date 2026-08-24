/*
Distribute Elements Into Two Arrays II - [Leetcode - 3072(HARD)]
--------------------------------------------------------------------
You are given a 1-indexed array of integers nums of length n.

We define a function greaterCount such that greaterCount(arr, val) returns the number of elements in arr that are strictly greater than val.

You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. Afterwards, in the ith operation:

If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with a lesser number of elements.
If there is still a tie, append nums[i] to arr1.
The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].

Return the integer array result. 

Example 1:

Input: nums = [2,1,3,3]
Output: [2,3,1,3]
Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
In the 3rd operation, the number of elements greater than 3 is zero in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
In the 4th operation, the number of elements greater than 3 is zero in both arrays. As the length of arr2 is lesser, hence, append nums[4] to arr2.
After 4 operations, arr1 = [2,3] and arr2 = [1,3].
Hence, the array result formed by concatenation is [2,3,1,3].

Example 2:

Input: nums = [5,14,3,1,2]
Output: [5,3,1,2,14]
Explanation: After the first 2 operations, arr1 = [5] and arr2 = [14].
In the 3rd operation, the number of elements greater than 3 is one in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
In the 4th operation, the number of elements greater than 1 is greater in arr1 than arr2 (2 > 1). Hence, append nums[4] to arr1.
In the 5th operation, the number of elements greater than 2 is greater in arr1 than arr2 (2 > 1). Hence, append nums[5] to arr1.
After 5 operations, arr1 = [5,3,1,2] and arr2 = [14].
Hence, the array result formed by concatenation is [5,3,1,2,14].

Example 3:

Input: nums = [3,3,3,3]
Output: [3,3,3,3]
Explanation: At the end of 4 operations, arr1 = [3,3] and arr2 = [3,3].
Hence, the array result formed by concatenation is [3,3,3,3]. 

Constraints:

3 <= n <= 10^5
1 <= nums[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class SegementTree {
public:
    int m;
    vector<int> segmentTree;

    // Constructor to initialize the segment tree with size m
    SegementTree(int size){
        m = size;
        segmentTree.resize(4 * m, 0); // Initialize the segment tree with zeros
    }

    void segementTreeUpdate(int node, int left, int right, int cv) {
        if (left == right) {
            segmentTree[node] += 1; // Increment the count at the leaf node
            return;
        }
        
        int mid = left + (right - left) / 2;
        
        if (cv <= mid) {
            segementTreeUpdate(2 * node + 1, left, mid, cv); // Update left child
        } else {
            segementTreeUpdate(2 * node + 2, mid + 1, right, cv); // Update right child
        }

        // After this, update parent node's value based on the values of its children
        segmentTree[node] = segmentTree[2 * node + 1] + segmentTree[2 * node + 2]; // Update current node
    }

    // Update Query
    void updateQuery(int cv) {
        // 0 -> index of root node in the segment tree
        // 0 -> start range of the segment tree
        // m-1 -> end range of the segment tree
        // cv -> compressed value of the element to be updated
        segementTreeUpdate(0, 0, m - 1, cv);
    }

    int segmentQueryRangeSum(int node, int left, int right, int start, int end) {
        if (start > right || end < left) {
            return 0; // No overlap
        }
        
        if (start <= left && right <= end) {
            return segmentTree[node]; // Total overlap
        }
        
        int mid = left + (right - left) / 2;
        
        // Partial overlap, query both children
        return segmentQueryRangeSum(2 * node + 1, left, mid, start, end) + segmentQueryRangeSum(2 * node + 2, mid + 1, right, start, end);
    }

    // Query Sum
    int querySum(int start, int end) {
        // 0 -> index of root node in the segment tree
        // 0 -> start range of the segment tree
        // m-1 -> end range of the segment tree
        // start -> start range of the query
        // end -> end range of the query
        return segmentQueryRangeSum(0, 0, m - 1, start, end);
    }
};

vector<int> resultArray(vector<int>& nums) {
    int n = nums.size();
    
    // Sort the nums array in ascending order
    vector<int> sortedNums(begin(nums), end(nums));
    sort(sortedNums.begin(), sortedNums.end());

    // Create a mapping from each element to its compressed Value
    unordered_map<int, int> map;
    int compressedValue = 0;
    for(auto num : sortedNums){ // Compressed Value given to nums
        if(!map.count(num)){
            map[num] = compressedValue++;
        }
    }

    int m = map.size(); // compressed valuess = 0, 1, ...., m-1;

    vector<int> arr1;
    vector<int> arr2;

    SegementTree segementTree1(m); // Segment Tree for arr1
    SegementTree segementTree2(m); // Segment Tree for arr2

    // 1st operation, append nums[0] to arr1
    arr1.push_back(nums[0]);
    segementTree1.updateQuery(map[nums[0]]);

    // 2nd operation, append nums[1] to arr2
    arr2.push_back(nums[1]);
    segementTree2.updateQuery(map[nums[1]]);

    for(int i = 2; i < n; i++){
        int cv = map[nums[i]]; // compressed value of nums[i]
        int count1 = segementTree1.querySum(cv+1, m-1); // number of elements > nums[i] in arr1
        int count2 = segementTree2.querySum(cv+1, m-1); // number of elements > nums[i] in arr2

        bool addToArr1 = false;
        if(count1 > count2){
            addToArr1 = true;
        } else if (count2 > count1){
            addToArr1 = false;
        } else {
            addToArr1 = arr1.size() <= arr2.size(); // If counts are equal, add to the array with lesser size
        }

        // Add nums[i] to the appropriate array and update the corresponding segment tree
        if(addToArr1){
            arr1.push_back(nums[i]);
            segementTree1.updateQuery(cv);
        } else {
            arr2.push_back(nums[i]);
            segementTree2.updateQuery(cv);
        }
    }

    // Concatenate the two arrays
    for(auto num : arr2){
        arr1.push_back(num);
    }
    return arr1;
}

int main() {
    vector<int> nums = {2, 1, 3, 3};
    vector<int> result = resultArray(nums);
    
    cout << "Result: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}