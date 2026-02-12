/*
Longest Balanced Subarray II - [Leetcode - 3721(Medium)]
-------------------------------------------------------------
You are given an integer array nums.

A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

Return the length of the longest balanced subarray.

Example 1:

Input: nums = [2,5,4,3]

Output: 4

Explanation:

The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.
Example 2:

Input: nums = [3,2,2,5,4]

Output: 5

Explanation:

The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.

Example 3:

Input: nums = [1,2,3,2]

Output: 3

Explanation:

The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include<unordered_map>
using namespace std;

//Approach-1 (Brute Force) - TLE
//T.C : O(n^2)
//S.C : O(n)
int longestBalanced(vector<int>& nums) {
    int n = nums.size();
    
    //treating even = +1 and odd = -1
    vector<int> cumSum(n, 0);
    
    int maxLength = 0;
    
    unordered_map<int, int> map;
    
    for(int r = 0; r < n; r++){
        int value = (nums[r] % 2 == 0) ? 1 : -1;
        
        int prevSeen = -1;
        
        if(map.count(nums[r])){
            prevSeen = map[nums[r]];
        }
        
        if(prevSeen != -1) { //we have seen this element in past
            // [0...prevSeen] We are adding (-value) in this range
            for(int l = 0; l <= prevSeen; l++){ // It is nothing but Range Query Update (RQU) in Segment Tree
                cumSum[l] -= value;
            }
        }
        
        // [0...r] We are adding (value) in this range
        for(int l = 0; l <= r; l++){
            cumSum[l] += value;
        }
        
        // We are finding leftmost most 0 in the range[0...r]
        for(int l = 0; l <= r; l++){
            if(cumSum[l] == 0) {
                maxLength = max(maxLength, r-l+1); // Here we are searching - segment tree query for leftmost 0 in the range [0...r]
                break;
            }
        }
        
        map[nums[r]] = r;
    }
    
    return maxLength;
}

//Approach - 2 (Using Segment Tree RMin Max Query
//T.C : O(nlogn)
//S.C : O(n)

void propagate(int i, int l, int r, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyArray) {
    if (lazyArray[i] != 0){
        minSegmentTree[i] += lazyArray[i];
        maxSegmentTree[i] += lazyArray[i];

        if (l != r){
            lazyArray[2*i+1] += lazyArray[i];
            lazyArray[2*i+2] += lazyArray[i];
        }
        lazyArray[i] = 0;
    }
}

// Range add value to [start, end]
void updateRange(int start, int end, int i, int l, int r, int value, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyArray) {
    propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyArray); //make sure to propagate before hand

    if (l > end || r < start) return;

    //[start...end[ is fully inside range of current node [l..r]
    if (l >= start && r <= end){
        lazyArray[i] += value;
        propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyArray);
        return;
    }

    int mid = (l + r) / 2;
    updateRange(start, end, 2*i+1, l, mid, value, minSegmentTree, maxSegmentTree, lazyArray);
    updateRange(start, end, 2*i+2, mid+1, r, value, minSegmentTree, maxSegmentTree, lazyArray);

    minSegmentTree[i] = min(minSegmentTree[2*i+1], minSegmentTree[2*i+2]);
    maxSegmentTree[i] = max(maxSegmentTree[2*i+1], maxSegmentTree[2*i+2]);
}

int findLeftMostZero(int i, int l, int r, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyArray) {
    propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyArray);

    if(minSegmentTree[i] > 0 || maxSegmentTree[i] < 0){
        return -1;
    }

    if(l == r){
        return l;
    }

    int mid = l + (r-l)/2;

    int leftResult = findLeftMostZero(2*i+1, l, mid, minSegmentTree, maxSegmentTree, lazyArray);
    
    if(leftResult != -1) return leftResult;
    
    return findLeftMostZero(2*i+2, mid+1, r, minSegmentTree, maxSegmentTree, lazyArray);
}

int longestBalanced(vector<int>& nums) {
    int n = nums.size();

    vector<int> minSegmentTree(4*n, 0);
    vector<int> maxSegmentTree(4*n, 0);
    vector<int> lazyArray(4*n, 0);
    
    int maxLength = 0;
    
    unordered_map<int, int> map;

    for(int r = 0; r < n; r++){
        int value = (nums[r] % 2 == 0) ? 1 : -1;
        
        int prevSeen = -1;
        
        if(map.count(nums[r])){
            prevSeen = map[nums[r]];
        }

        if(prevSeen != -1){ // we have seen this element in past
            // [0...prevSeen] We are adding (-value) in this range
            updateRange(0, prevSeen, 0, 0, n-1, -value, minSegmentTree, maxSegmentTree, lazyArray); // It is nothing but Range Query Update (RQU) in Segment Tree
        }

        // [0...r] We are adding (value) in this range
        updateRange(0, r, 0, 0, n-1, value, minSegmentTree, maxSegmentTree, lazyArray);

        // We are finding leftmost most 0 in the range[0...r]
        int l = findLeftMostZero(0, 0, n-1, minSegmentTree, maxSegmentTree, lazyArray); // Here we are searching - segment tree query for leftmost 0 in the range [0...r]
        
        if(l != -1){
            maxLength = max(maxLength, r-l+1);
        }

        map[nums[r]] = r;
    }
    return maxLength;
}

int main() {
    vector<int> nums1 = {2, 5, 4, 3};
    cout << longestBalanced(nums1) << endl; // Output: 4

    vector<int> nums2 = {3, 2, 2, 5, 4};
    cout << longestBalanced(nums2) << endl; // Output: 5

    vector<int> nums3 = {1, 2, 3, 2};
    cout << longestBalanced(nums3) << endl; // Output: 3

    return 0;
}
