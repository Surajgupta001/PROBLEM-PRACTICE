/*
Find Minimum Diameter After Merging Two Trees - [Leetcode - 3203(Medium)]
-----------------------------------------------------------------------------
There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

You must connect one node from the first tree with another node from the second tree with an edge.

Return the minimum possible diameter of the resulting tree.

The diameter of a tree is the length of the longest path between any two nodes in the tree.

Example 1:

Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]

Output: 3

Explanation:

We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.

Example 2:

Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]

Output: 5

Explanation:

We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.

Constraints:

1 <= n, m <= 105
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
*/

// LEETCODE - 3203 => Similar problem : 1245_Tree_Diameter.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// BFS : function to find the farthest node and its distance from the source node
pair<int, int> findFarthestNode(vector<vector<int>>& graph, int sourceNode) {
    queue<int> qu;
    vector<bool> visited(graph.size(), false);

    // Push source node into the queue and mark it as visited
    qu.push(sourceNode);
    visited[sourceNode] = true;

    int maximumDistance = 0;
    int farthestNode = sourceNode;

    // Explore the graph using BFS
    while(!qu.empty()){
        int size = qu.size();
        for(int i = 0; i < size; i++){
            int currentNode = qu.front();
            qu.pop();

            // Update the farthest node and maximum distance
            farthestNode = currentNode;

            for(auto &neighbor : graph[currentNode]){
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    qu.push(neighbor);
                }
            }
        }
        maximumDistance++;
    }

    return {farthestNode, maximumDistance - 1};
}

int findDiameter(vector<vector<int>>& graph) {
    // Perform the first BFS to find the farthest node from an arbitrary starting node (0 in this case)
    pair<int, int> firstBFS = findFarthestNode(graph, 0);

    // Perform the second BFS from the farthest node found in the first BFS to find the diameter
    pair<int, int> secondBFS = findFarthestNode(graph, firstBFS.first);

    // The diameter of the tree is the maximum distance found in the second BFS
    return secondBFS.second;
}

int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
    int n = edges1.size() + 1;
    int m = edges2.size() + 1;

    vector<vector<int>> graph1(n);

    // Build the graph for the first tree
    for (auto& edge : edges1) {
        graph1[edge[0]].push_back(edge[1]);
        graph1[edge[1]].push_back(edge[0]);
    }

    vector<vector<int>> graph2(m);

    // Build the graph for the second tree
    for (auto& edge : edges2) {
        graph2[edge[0]].push_back(edge[1]);
        graph2[edge[1]].push_back(edge[0]);
    }

    int diameter1 = findDiameter(graph1);
    int diameter2 = findDiameter(graph2);

    return max({diameter1, diameter2, (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1});
}

int main () {
    vector<vector<int>> edges1 = {{0,1},{0,2},{0,3}};
    vector<vector<int>> edges2 = {{0,1}};

    cout << minimumDiameterAfterMerge(edges1, edges2) << endl; // Output: 3

    vector<vector<int>> edges3 = {{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};
    vector<vector<int>> edges4 = {{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};

    cout << minimumDiameterAfterMerge(edges3, edges4) << endl; // Output: 5

    return 0;
}