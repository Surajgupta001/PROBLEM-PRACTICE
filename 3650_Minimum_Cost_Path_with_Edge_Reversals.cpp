/*
Minimum Cost Path with Edge Reversals - [Leetcode - 3650(Medium)]
--------------------------------------------------------------------
You are given a directed, weighted graph with n nodes labeled from 0 to n - 1, and an array edges where edges[i] = [ui, vi, wi] represents a directed edge from node ui to node vi with cost wi.

Each node ui has a switch that can be used at most once: when you arrive at ui and have not yet used its switch, you may activate it on one of its incoming edges vi → ui reverse that edge to ui → vi and immediately traverse it.

The reversal is only valid for that single move, and using a reversed edge costs 2 * wi.

Return the minimum total cost to travel from node 0 to node n - 1. If it is not possible, return -1.

Example 1:

Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]

Output: 5

Explanation:

Use the path 0 → 1 (cost 3).
At node 1 reverse the original edge 3 → 1 into 1 → 3 and traverse it at cost 2 * 1 = 2.
Total cost is 3 + 2 = 5.
Example 2:

Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]

Output: 3

Explanation:

No reversal is needed. Take the path 0 → 2 (cost 1), then 2 → 1 (cost 1), then 1 → 3 (cost 1).
Total cost is 1 + 1 + 1 = 3.
 

Constraints:

2 <= n <= 5 * 10^4
1 <= edges.length <= 10^5
edges[i] = [ui, vi, wi]
0 <= ui, vi <= n - 1
1 <= wi <= 1000
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Dijkstra's algorithm to find the minimum cost path with edge reversals
int minCost(int n, vector<vector<int>>& edges) {

    // Build the graph with adjacency list representation
    vector<vector<pair<int, int>>> graph(n);

    for(auto &edge : edges){
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        graph[u].push_back({v, w}); // Original edge with cost w
        graph[v].push_back({u, 2 * w}); // Reversed edge with cost 2*w
    }

    // Max heap priority queue to store (cost, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> result(n, INT_MAX); // result[i] = distance of source = 0 with node i
    result[0] = 0;
    pq.push({0, 0}); // Start from node 0 with cost 0

    // Dijkstra's algorithm
    while(!pq.empty()){
        int distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(node == n - 1){
            return result[n-1]; // Return the cost to reach node n-1
        }

        for(auto &neighbor : graph[node]){
            int adjNode = neighbor.first;
            int edgeCost = neighbor.second;

            if(distance + edgeCost < result[adjNode]){
                result[adjNode] = distance + edgeCost;
                pq.push({result[adjNode], adjNode});
            }
        }
    }
    return -1; // If node n-1 is not reachable
}

int main() {
    
    int n = 4;
    
    vector<vector<int>> edges = {{0,1,3},{3,1,1},{2,3,4},{0,2,2}};
    
    cout << "Minimum Cost Path: " << minCost(n, edges) << endl; // Output: 5
    
    return 0;
}