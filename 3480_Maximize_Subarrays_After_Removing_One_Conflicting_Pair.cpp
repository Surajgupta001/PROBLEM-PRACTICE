/*
Maximize Subarrays After Removing One Conflicting Pair - [LeetCode - Hard(3480)]
---------------------------------------------------------------------------------
You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.

Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].

Return the maximum number of subarrays possible after removing exactly one conflicting pair.

 

Example 1:

Input: n = 4, conflictingPairs = [[2,3],[1,4]]

Output: 9

Explanation:

Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
Example 2:

Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]

Output: 12

Explanation:

Remove [1, 2] from conflictingPairs. Now, conflictingPairs = [[2, 5], [3, 5]].
There are 12 subarrays in nums where [2, 5] and [3, 5] do not appear together.
The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 12.
 

Constraints:

2 <= n <= 105
1 <= conflictingPairs.length <= 2 * n
conflictingPairs[i].length == 2
1 <= conflictingPairs[i][j] <= n
conflictingPairs[i][0] != conflictingPairs[i][1]
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define ALL(x) begin(x), end(x)
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        long long valid = 0;

        
        vector<vector<int>> conflictingPoints(n+1);
        //conflictingPoints[i] = {points which confliuct with i}

        for(auto &p : conflictingPairs) { //O(C)
            //(a, b)
            int a = min(p[0], p[1]);
            int b = max(p[0], p[1]);

            conflictingPoints[b].push_back(a); //{1,2,a,,,,b}
        }

        int maxConflict = 0;
        int secondMaxConflict = 0;

        vector<long long> extra(n+1, 0);
        //extra[i] = number of extra subarrays by removing the conflicting point i

        //O(n+P)
        //O(n)
        for(int end = 1; end <= n; end++) { //visiting each point and treating them as subarray ending at this point
            //total subarrays ending at this point 'end'
            
            //O(P)
            for(int &u : conflictingPoints[end]) { //check all conflicting points of end
                if(u >= maxConflict) {
                    secondMaxConflict = maxConflict;
                    maxConflict = u;
                } else if(u > secondMaxConflict) {
                    secondMaxConflict = u;
                }
            }

            valid += end - maxConflict;
            extra[maxConflict] += maxConflict - secondMaxConflict;
        }


        return valid + *max_element(ALL(extra)); //you could also write valid + *max_element(begin(extra), end(extra))
    }
};