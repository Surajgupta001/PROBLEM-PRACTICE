/*
Find Center of Star Graph - [Leetcode - 1791(Easy)]
----------------------------------------------------
There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.

Example 1:

Input: edges = [[1,2],[2,3],[4,2]]
Output: 2
Explanation: As shown in the figure above, node 2 is connected to every other node, so 2 is the center.

Example 2:

Input: edges = [[1,2],[5,1],[1,3],[1,4]]
Output: 1
 

Constraints:

3 <= n <= 105
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
ui != vi
The given edges represent a valid star grap
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Approach-1: Using HashMap
int findCenter(vector<vector<int>>& edges) {
    int n = edges.size() + 1; // Number of nodes
    vector<int> degree(n + 1, 0); // Degree array to count edges for each node

    // Count the degree of each node
    for (auto& edge : edges) {
        degree[edge[0]]++;
        degree[edge[1]]++;
    }

    // The center node will have a degree of n - 1
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == n - 1) {
            return i;
        }
    }

    return -1; // This line should never be reached for a valid star graph
}

// Approach-2: Using Degree Array
int findCenter(vector<vector<int>>& edges) {
    // Since it's a star graph, the center node will appear in at least two edges.
    int a = edges[0][0]; // First edge
    int b = edges[0][1]; // First edge

    // Check which node from first edge is present in second edge
    int c = edges[1][0]; // Second edge
    int d = edges[1][1]; // Second edge

    // One of the nodes from first edge must be the center
    return (c == a || c == b) ? c : d;
}

int main() {
    vector<vector<int>> edges1 = {{1, 2}, {2, 3}, {4, 2}};
    vector<vector<int>> edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};

    cout << "Center of star graph (Example 1): " << findCenter(edges1) << endl; // Output: 2
    cout << "Center of star graph (Example 2): " << findCenter(edges2) << endl; // Output: 1

    return 0;
}