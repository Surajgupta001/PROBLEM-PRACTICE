/*
Bitwise ORs of Subarrays - [Leetcode - 898(Medium)]
-----------------------------------------------------
Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.

The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: arr = [0]
Output: 1
Explanation: There is only one possible result: 0.

Example 2:

Input: arr = [1,1,2]
Output: 3
Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.

Example 3:

Input: arr = [1,2,4]
Output: 6
Explanation: The possible results are 1, 2, 3, 4, 6, and 7.


Constraints:

1 <= arr.length <= 5 * 104
0 <= arr[i] <= 109
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Brute Force Approach => O(n^3) time complexity
int subarrayBitwiseORs(vector<int> &arr){
    unordered_set<int> sets;
    int n = arr.size();

    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            int orValue = 0;
            for (int k = i; k <= j; k++){
                orValue |= arr[k];
            }
            sets.insert(orValue);
        }
    }
    return sets.size();
}

// Optimized Approach => O(n) time complexity
int subarrayBitwiseORs(vector<int> &arr){
    unordered_set<int> prev;
    unordered_set<int> curr;
    unordered_set<int> result;

    for (int i = 0; i < arr.size(); i++){

        for (auto &x : prev){
            curr.insert(x | arr[i]);
            result.insert(x | arr[i]);
        }

        curr.insert(arr[i]);
        result.insert(arr[i]);

        prev = curr;
        curr.clear();
    }

    return result.size();
}

int main(){
    vector<int> arr = {1, 2, 4};
    cout << "Number of distinct bitwise ORs: " << subarrayBitwiseORs(arr) << endl;
    return 0;
}