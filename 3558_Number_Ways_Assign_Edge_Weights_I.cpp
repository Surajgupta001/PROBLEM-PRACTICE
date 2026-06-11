/*
Number of Ways to Assign Edge Weights I - [Leetcode - 3558(Medium)]
---------------------------------------------------------------------

There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.

Since the answer may be large, return it modulo 109 + 7.

Note: Ignore all edges not in the path from node 1 to x.

Example 1:

Input: edges = [[1,2]]

Output: 1

Explanation:

The path from Node 1 to Node 2 consists of one edge (1 → 2).
Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.

Example 2:

Input: edges = [[1,2],[1,3],[3,4],[3,5]]

Output: 2

Explanation:

The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4).
Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
 

Constraints:

2 <= n <= 10^5
edges.length == n - 1
edges[i] == [ui, vi]
1 <= ui, vi <= n
edges represents a valid tree.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
int mod = 1e9 + 7;

ll power(ll base, ll exp) {
    if(exp == 0) return 1;

    ll half = power(base, exp / 2);

    ll result = (half * half) % mod;

    if(exp % 2 == 1) {
        result = (result * base) % mod;
    }
    return result;
}

// Here finding maxDepth in similar wise to find in binary tree -> here it is undirected tree
int getMaxDepth(vector<vector<int>>& graph, int node, int parent) {
    int depth = 0;

    for(auto &neighbor : graph[node]){
        if(neighbor != parent) {
            depth = max(depth, getMaxDepth(graph, neighbor, node));
        }
    }
    return depth + 1;
}

int assignEdgeWeights(vector<vector<int>>& edges) {

    // Build the Graph
    int n = edges.size() + 1;
    vector<vector<int>> graph(n + 1);

    for(auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Find the maximum depth
    int depth = getMaxDepth(graph, 1, -1);

    return power(2, depth-2);
}

int main() {
    vector<vector<int>> edges = {{1,2},{1,3},{3,4},{3,5}};
    cout << assignEdgeWeights(edges) << endl; // Output: 2
    return 0;
}