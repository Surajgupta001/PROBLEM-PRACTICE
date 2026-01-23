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
using namespace std;

class Solution {
    public:
        typedef long long ll;
    
        int minimumPairRemoval(vector<int>& nums) {
            int n = nums.size();
    
            //{a, b, c, d} --> {a, b+c, d}
            vector<ll> temp(n);
            for(int i = 0; i < n; i++)
                temp[i] = nums[i];
    
            set<pair<ll, int>> minPairSet;
    
            vector<int> nextIndex(n);
            vector<int> prevIndex(n);
    
            for(int i = 0; i < n; i++) {
                nextIndex[i] = i+1;
                prevIndex[i] = i-1;
            }
    
            int badPairs = 0;
            for(int i = 0; i < n-1; i++) {
                if(temp[i] > temp[i+1]) {
                    badPairs++;
                }
                minPairSet.insert({temp[i] + temp[i+1], i});
            }
    
            int operations = 0;
    
            while(badPairs > 0) {
                int first  = minPairSet.begin()->second;
                int second = nextIndex[first];
    
                int first_left   = prevIndex[first];
                int second_right = nextIndex[second];
    
    
                minPairSet.erase(begin(minPairSet));
    
                if(temp[first] > temp[second]) {
                    badPairs--;
                }
    
                //{d, (a, b)}
                if(first_left >= 0) {
                    if(temp[first_left] > temp[first] &&
                    temp[first_left] <= temp[first] + temp[second]) {
                        badPairs--;
                    } 
                    else if(temp[first_left] <= temp[first] &&
                    temp[first_left] > temp[first] + temp[second]) {
                        badPairs++;
                    }
                }
    
                //{(a, b), d}
                if (second_right < n) {
                    if (temp[second_right] >= temp[second] &&
                        temp[second_right] < temp[first] + temp[second]) {
                        badPairs++;
                    }
                    else if (temp[second_right] < temp[second] &&
                             temp[second_right] >= temp[first] + temp[second]) {
                        badPairs--;
                    }
                }
    
                if(first_left >= 0) {
                    minPairSet.erase({temp[first_left] + temp[first], first_left});
                    minPairSet.insert({temp[first_left] + temp[first] + temp[second], first_left});
                }
    
                if(second_right < n) {
                    minPairSet.erase({temp[second] + temp[second_right], second});
                    minPairSet.insert({temp[first] + temp[second] + temp[second_right], first});
                    prevIndex[second_right] = first;
                }
    
                nextIndex[first] = second_right;
                temp[first] += temp[second];
    
                operations++;
            }
    
            return operations;
        }
    };
    