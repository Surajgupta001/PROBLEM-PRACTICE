/*
Closest Equal Element Queries - [Leetcode - 3488(Medium)]
-----------------------------------------------------------
You are given a circular array nums and an array queries.

For each query i, you have to find the following:

The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
Return an array answer of the same size as queries, where answer[i] represents the result for query i.

Example 1:

Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]

Output: [2,-1,3]

Explanation:

Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).

Example 2:

Input: nums = [1,2,3,4], queries = [0,1,2,3]

Output: [-1,-1,-1,-1]

Explanation:

Each value in nums is unique, so no index shares the same value as the queried element. This results in -1 for all queries.

Constraints:

1 <= queries.length <= nums.length <= 10^5
1 <= nums[i] <= 10^6
0 <= queries[i] < nums.length
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
    int n = nums.size();
    unordered_map<int, vector<int>> indexMap;

    // Build a map of value to its indices
    for (int i = 0; i < n; ++i) {
        indexMap[nums[i]].push_back(i);
    }

    vector<int> results;
    
    for(auto &qi: queries){
        int element = nums[qi];
        vector<int> &indices = indexMap[element];

        int sz = indices.size();

        if(sz == 1){ // No more occurrence of this element
            results.push_back(-1);
            continue;
        }

        int position = lower_bound(indices.begin(), indices.end(), qi) - indices.begin();
        int result = INT_MAX;

        // Right Neighbour - pos+1
        int right = indices[(position + 1) % sz];
        int d = abs(qi - right); // Straight Forward distance
        int circularDistance = n - d; // Circular distance
        result = min({d, circularDistance, result});

        // Left Neighbour - pos-1
        int left = indices[(position - 1 + sz) % sz];
        d = abs(qi - left); // Straight Forward distance
        circularDistance = n - d;
        result = min({d, circularDistance, result});

        results.push_back(result);
    }
    return results;
}

int main() {
    vector<int> nums = {1, 3, 1, 4, 1, 3, 2};
    vector<int> queries = {0, 3, 5};

    vector<int> results = solveQueries(nums, queries);
    for (int res : results) {
        cout << res << " ";
    }
    cout << endl;

    return 0;
}