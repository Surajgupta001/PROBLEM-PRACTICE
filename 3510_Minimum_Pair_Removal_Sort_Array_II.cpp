/*
Minimum Pair Removal to Sort Array II - [Leetcode - 3510(HARD)]
-------------------------------------------------------------------
Given an array nums, you can perform the following operation any number of times:

Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
Replace the pair with their sum.
Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).

Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.

Constraints:

1 <= nums.length <= 10^5
-109 <= nums[i] <= 10^9
*/ 

#include <iostream>
#include <vector>
#include<set>
using namespace std;

int minimumPairRemoval(vector<int>& nums) {
    int n = nums.size();

    // {a, b, c, d} => {a, b + c, d} if b + c >= a and b + c <= d
    vector<long long> temp(n); // to avoid integer overflow make it long long instead of int
    for (int i = 0; i < n; i++) {
        temp[i] = nums[i];
    }

    int operations = 0;

    set<pair<long long, int>> minPairSet; // {sum, index}

    vector<int> prevIndex(n);
    vector<int> nextIndex(n);

    for(int i = 0; i < n; i++){
        prevIndex[i] = i - 1;
        nextIndex[i] = i + 1;
    }

    int badPairs = 0;
    for(int i=0; i<n; i++){
        if(temp[i] > temp[i+1]){ // that means it's decreasing pair
            badPairs++;
        }
        minPairSet.insert({temp[i] + temp[i+1], i});
    }

    while(badPairs > 0){ // that means array is not sorted yet
        int first = minPairSet.begin()->second; // index of first element of the minimum sum pair
        int second = nextIndex[first]; // index of second element of the minimum sum pair

        int first_left = prevIndex[first]; // index of left element of the first element
        int second_right = nextIndex[second]; // index of right element of the second element

        minPairSet.erase(minPairSet.begin()); // remove the current minimum sum pair

        if(temp[first] > temp[second]){ // that means it's a bad pair
            badPairs--; // removing a bad pair
        }

        // {d, (a, b)}
        if(first_left >= 0){
            if(temp[first_left] > temp[first] && temp[first_left] <= temp[first] + temp[second]){
                badPairs--; // removing a bad pair
            } else if(temp[first_left] <= temp[first] && temp[first_left] > temp[first] + temp[second]){
                badPairs++; // adding a bad pair
            }
        }

        // {(a, b), c}
        if(second_right < n){
            if(temp[second_right] >= temp[second] && temp[second_right] < temp[first] + temp[second]){
                badPairs--; // removing a bad pair
            } else if(temp[second_right] < temp[second] && temp[second_right] >= temp[first] + temp[second]){
                badPairs++; // adding a bad pair
            }
        }

        // update the temp array
        if(first_left >= 0){
            minPairSet.erase({temp[first_left] + temp[first], first_left});
            minPairSet.insert({temp[first_left] + (temp[first] + temp[second]), first_left});
        }

        // update the temp array
        if(second_right < n){
            minPairSet.erase({temp[second] + temp[second_right], second});
            minPairSet.insert({(temp[first] + temp[second]) + temp[second_right], first});
            prevIndex[second_right] = first;
        }

        nextIndex[first] = second_right;
        temp[first] += temp[second];

        operations++;
    }

    return operations;
}

int main() {
    vector<int> nums = {5, 2, 3, 1};
    cout << "Minimum operations to sort the array: " << minimumPairRemoval(nums) << endl;
    return 0;
}