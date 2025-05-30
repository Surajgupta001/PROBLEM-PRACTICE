/*
Maximize the Number of Target Nodes After Connecting Trees II - [Leetcode - 3373(Hard)]
---------------------------------------------------------------------------------------
There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.

You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

Node u is target to node v if the number of edges on the path from u to v is even. Note that a node is always target to itself.

Return an array of n integers answer, where answer[i] is the maximum possible number of nodes that are target to node i of the first tree if you had to connect one node from the first tree to another node in the second tree.

Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.

Example 1:

Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]

Output: [8,7,7,8,8]

Explanation:

For i = 0, connect node 0 from the first tree to node 0 from the second tree.
For i = 1, connect node 1 from the first tree to node 4 from the second tree.
For i = 2, connect node 2 from the first tree to node 7 from the second tree.
For i = 3, connect node 3 from the first tree to node 0 from the second tree.
For i = 4, connect node 4 from the first tree to node 4 from the second tree.

Example 2:

Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]

Output: [3,6,6,6,6]

Explanation:

For every i, connect node i of the first tree with any node of the second tree.

Constraints:

2 <= n, m <= 105
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
*/ 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dfs(int currNode, vector<vector<int>> &graph, int parent, vector<int>& mark, int &zeroMarkedCount, int &oneMarkedCount){
    
    if(mark[currNode] == 0){ // 0 means even marking
        zeroMarkedCount++; // Increment count of nodes marked as 0
    }
    else {
        oneMarkedCount++; // Increment count of nodes marked as 1
    }

    for(auto &neighbor : graph[currNode]) { // Traversing all neighbors of the current node
        if(neighbor != parent){ // Avoid going back to the parent node
            mark[neighbor] = (mark[currNode] == 0 ? 1 : 0); // Alternate marking
            dfs(neighbor, graph, currNode, mark, zeroMarkedCount, oneMarkedCount);
        }
    }
}

void bfs(int root, vector<vector<int>>& graph, vector<int>& mark, int& zeroMarkedCount, int& oneMarkedCount) {
    queue<int> q;
    q.push(root);
    mark[root] = 0; // Start with even marking

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (mark[curr] == 0) zeroMarkedCount++;
        else oneMarkedCount++;

        for (int neighbor : graph[curr]) {
            if (mark[neighbor] == -1) {
                mark[neighbor] = 1 - mark[curr]; // Alternate marking
                q.push(neighbor);
            }
        }
    }
}

vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
    int n = edges1.size() + 1; // Tree 1 has n nodes
    int m = edges2.size() + 1; // Tree 2 has m nodes

    // Build Graph for first trees
    vector<vector<int>> graph1(n);
    for (const auto& edge : edges1) {
        graph1[edge[0]].push_back(edge[1]);
        graph1[edge[1]].push_back(edge[0]);
    }

    vector<vector<int>> graph2(m);
    // Build Graph for second tree
    for (const auto& edge : edges2) {
        graph2[edge[0]].push_back(edge[1]);
        graph2[edge[1]].push_back(edge[0]);
    }

    vector<int> markA(n, -1); // -1 means unmarked, 0 means even, 1 means odd
    markA[0] = 0; // Mark 0th node as 0
    int zeroMarkedCountA = 0; // Count of nodes marked as 0
    int oneMarkedCountA = 0; // Count of nodes marked as 1
    
    // Start DFS from the root node (0) of the first tree
    dfs(0, graph1, -1, markA, zeroMarkedCountA, oneMarkedCountA);

    // Start BFS from the root node (0) of the first tree
    // bfs(0, graph1, markA, zeroMarkedCountA, oneMarkedCountA);

    vector<int> markB(m, -1); // -1 means unmarked, 0 means even, 1 means odd
    markB[0] = 0; // Mark 0th node as 0
    int zeroMarkedCountB = 0; // Count of nodes marked as 0
    int oneMarkedCountB = 0; // Count of nodes marked as 1
    
    // Start DFS from the root node (0) of the second tree
    dfs(0, graph2, -1, markB, zeroMarkedCountB, oneMarkedCountB);

    // Start BFS from the root node (0) of the second tree
    // bfs(0, graph2, markB, zeroMarkedCountB, oneMarkedCountB);

    int maxFromTree2 = max(zeroMarkedCountB, oneMarkedCountB); // Maximum nodes that can be connected from tree 2

    vector<int> answer(n);
    for(int i=0; i<n; i++){
        // answer[i] = (markA[i] == 0 ? zeroMarkedCountA : oneMarkedCountA) + maxFromTree2;
        int marking = markA[i]; // Get the marking of the current node in tree 1
        if(marking == 0){ // If the node is marked as 0 (even)
            answer[i] = zeroMarkedCountA + maxFromTree2; // Count of nodes marked as 0 in tree 1 + max from tree 2
        }
        else {
            answer[i] = oneMarkedCountA + maxFromTree2; // Count of nodes marked as 1 in tree 1 + max from tree 2
        }
    }

    return answer;
}

int main() {

    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}};

    vector<int> result = maxTargetNodes(edges1, edges2);
    
    for(int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}