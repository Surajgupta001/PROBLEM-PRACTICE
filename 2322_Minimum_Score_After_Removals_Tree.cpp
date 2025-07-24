/*
Minimum Score After Removals on a Tree - [Leetcode - 2322(Hard)]
------------------------------------------------------------------
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:

Get the XOR of all the values of the nodes for each of the three components respectively.
The difference between the largest XOR value and the smallest XOR value is the score of the pair.
For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
Return the minimum score of any possible pair of edge removals on the given tree.

 

Example 1:

Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
Output: 9
Explanation: The diagram above shows a way to make a pair of removals.
- The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
- The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
- The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
It can be shown that no other pair of removals will obtain a smaller score than 9.

Example 2:

Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
Output: 0
Explanation: The diagram above shows a way to make a pair of removals.
- The 1st component has nodes [3,4] with values [4,4]. Its XOR value is 4 ^ 4 = 0.
- The 2nd component has nodes [1,0] with values [5,5]. Its XOR value is 5 ^ 5 = 0.
- The 3rd component has nodes [2,5] with values [2,2]. Its XOR value is 2 ^ 2 = 0.
The score is the difference between the largest and smallest XOR value which is 0 - 0 = 0.
We cannot obtain a smaller score than 0.
 

Constraints:

n == nums.length
3 <= n <= 1000
1 <= nums[i] <= 108
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.

*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void dfs(int node, int parent, vector<int>& subtreeXor, vector<int>& inTime, vector<int>& outTime, int& timer, vector<int>& nums, vector<vector<int>>& graph) {
    subtreeXor[node] = nums[node];
    inTime[node] = timer++;

    for(auto neighbor : graph[node]) {
        if(neighbor != parent) {
            dfs(neighbor, node, subtreeXor, inTime, outTime, timer, nums, graph);
            subtreeXor[node] ^= subtreeXor[neighbor];
        }
    }

    outTime[node] = timer++;
}

bool isAncestor(int u, int v, vector<int>& inTime, vector<int>& outTime) {
    return inTime[u] <= inTime[v] && outTime[u] >= outTime[v];
}

int getScore(int xor1, int xor2, int xor3) {
    return max({xor1, xor2, xor3}) - min({xor1, xor2, xor3});
}

int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
    int n = nums.size();
    
    // Graph building
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> subtreeXor(n, 0);

    vector<int> inTime(n, 0);
    vector<int> outTime(n, 0);

    int timer = 0;

    // Treating root as 0
    dfs(0, -1, subtreeXor, inTime, outTime, timer, nums, graph);

    int result = INT_MAX;

    for(int u=1; u<n; u++){
        for(int v=u+1; v<n; v++){
            int xor1;
            int xor2;
            int xor3;

            if(isAncestor(u, v, inTime, outTime)) {
                xor1 = subtreeXor[v];
                xor2 = subtreeXor[u] ^ subtreeXor[v];
                xor3 = subtreeXor[0] ^ subtreeXor[u];
            } else if(isAncestor(v, u, inTime, outTime)) {
                xor1 = subtreeXor[u];
                xor2 = subtreeXor[v] ^ subtreeXor[u];
                xor3 = subtreeXor[0] ^ subtreeXor[v];
            } else {
                xor1 = subtreeXor[u];
                xor2 = subtreeXor[v];
                xor3 = subtreeXor[0] ^ (xor1 ^ xor2);
            }

            result = min(result, getScore(xor1, xor2, xor3));
        }
    }

    return result;
}

int main() {
    vector<int> nums = {1, 5, 5, 4, 11};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}};
    
    cout << "Minimum Score: " << minimumScore(nums, edges) << endl; // Output: 9

    return 0;
}