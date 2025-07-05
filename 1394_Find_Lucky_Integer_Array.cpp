/*
Find Lucky Integer in an Array - [Leetcode - 1394(Easy)]
----------------------------------------------------------
Given an array of integers arr, a lucky integer is an integer that has a frequency in the array equal to its value.

Return the largest lucky integer in the array. If there is no lucky integer return -1.



Example 1:

Input: arr = [2,2,3,4]
Output: 2
Explanation: The only lucky number in the array is 2 because frequency[2] == 2.
Example 2:

Input: arr = [1,2,2,3,3,3]
Output: 3
Explanation: 1, 2 and 3 are all lucky numbers, return the largest of them.
Example 3:

Input: arr = [2,2,2,3,3]
Output: -1
Explanation: There are no lucky numbers in the array.


Constraints:

1 <= arr.length <= 500
1 <= arr[i] <= 500
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int findLucky(vector<int> &arr){
    int n = arr.size();

    for (int &num : arr){
        int val = (num & 65535);

        if (val <= n){
            arr[val - 1] += (1 << 16); // 65536, pow(2, 16)
        }
    }

    for (int val = n; val >= 1; val--){
        if ((arr[val - 1] >> 16) == val){
            return val;
        }
    }

    return -1;
}