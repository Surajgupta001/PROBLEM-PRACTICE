/*
Tree Diameter - [Leetcode - 1245(Medium)]
--------------------------------------------
The diameter of a tree is the number of edges in the longest path in that tree.

There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the tree.

Return the diameter of the tree.

Example 1:

Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: The longest path of the tree is the path 1 - 0 - 2.

Example 2:

Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: The longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 
Constraints:

n == edges.length + 1
1 <= n <= 10^4
0 <= ai, bi < n
ai != bi
*/

// Leetcode - 3203 => Similar problem

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Approach (Using BFS)
//T.C : O(V+E)
//S.C : O(V+E)
pair<int, int> findFarthestNode(int n, vector<vector<int>>& graph, int sourceNode) {
    queue<int> qu;
    vector<bool> visited(n, false);

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
        if(!qu.empty()){
            maximumDistance++;
        }
    }
    return {farthestNode, maximumDistance};
}

int findDiameter(int n, vector<vector<int>>& graph) {
    // Perform the first BFS to find the farthest node from an arbitrary starting node (0 in this case)
    pair<int, int> firstBFS = findFarthestNode(n, graph, 0);

    // Perform the second BFS from the farthest node found in the first BFS to find the diameter
    pair<int, int> secondBFS = findFarthestNode(n, graph, firstBFS.first);

    // The diameter of the tree is the maximum distance found in the second BFS
    return secondBFS.second;
}

int treeDiameter(vector<vector<int>>& edges) {
    // Number of nodes in the tree
    int n = edges.size() + 1;

    // Build the graph
    vector<vector<int>> graph(n);
    for(auto &edge : edges){
        int u = edge[0];
        int v = edge[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Find the diameter of the tree
    return findDiameter(n, graph);
}

int main() {
    vector<vector<int>> edges1 = {{0,1},{0,2}};
    cout << "Diameter of the tree: " << treeDiameter(edges1) << endl; // Output: 2

    vector<vector<int>> edges2 = {{0,1},{1,2},{2,3},{1,4},{4,5}};
    cout << "Diameter of the tree: " << treeDiameter(edges2) << endl; // Output: 4

    return 0;
}