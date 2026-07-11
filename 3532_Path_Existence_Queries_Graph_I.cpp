/*
Path Existence Queries in a Graph I - [Leetcode - 3532(Medium)]
---------------------------------------------------------------------

You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.

You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.

An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).

You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.

Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.

Example 1:

Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]

Output: [true,false]

Explanation:

Query [0,0]: Node 0 has a trivial path to itself.
Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
Thus, the final answer after processing all the queries is [true, false].

Example 2:

Input: n = 4, nums = [2,5,6,8], maxDiff = 2, queries = [[0,1],[0,2],[1,3],[2,3]]

Output: [false,false,true,true]

Explanation:

The resulting graph is:


Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |2 - 5| = 3, which is greater than maxDiff.
Query [0,2]: There is no edge between Node 0 and Node 2 because |nums[0] - nums[2]| = |2 - 6| = 4, which is greater than maxDiff.
Query [1,3]: There is a path between Node 1 and Node 3 through Node 2 since |nums[1] - nums[2]| = |5 - 6| = 1 and |nums[2] - nums[3]| = |6 - 8| = 2, both of which are within maxDiff.
Query [2,3]: There is an edge between Node 2 and Node 3 because |nums[2] - nums[3]| = |6 - 8| = 2, which is equal to maxDiff.
Thus, the final answer after processing all the queries is [false, false, true, true].
 

Constraints:

1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
nums is sorted in non-decreasing order.
0 <= maxDiff <= 10^5
1 <= queries.length <= 10^5
queries[i] == [ui, vi]
0 <= ui, vi < n
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//Approach-1 (Using DFS for each query) - TLE
//T.C : O(q * (V+E)), q = number of queries, V + E is for DFS, V = number of vertices, E = number of edges
//S.C : O(V+E), V = number of vertices, E = number of edges
bool dfs(int cur, int target, unordered_map<int, vector<int>>& graph, vector<bool>& visited) {
    if (cur == target) return true;
    
    visited[cur] = true;
    
    for (int& ngbr : graph[cur]) {
        if (!visited[ngbr]) {
            if (dfs(ngbr, target, graph, visited)) 
                return true;
        }
    }

    return false;
}
vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    unordered_map<int, vector<int>> graph;
    
    for (int i = 0; i + 1 < n; i++) {
        if (nums[i + 1] - nums[i] <= maxDiff) {
            graph[i].push_back(i + 1);
            graph[i + 1].push_back(i);
        }
    }
    
    vector<bool> result;
    
    for (auto& query : queries) {
        int u = query[0];
        int v = query[1];
        vector<bool> visited(n, false);
        result.push_back(dfs(u, v, graph, visited));
    }
    return result;
}

//Approach-2 (Using DFS once and then mark component) - TLE
//T.C : O((V+E) + q), V + E is for DFS, V = number of vertices, E = number of edges
//S.C : O(V+E), V = number of vertices, E = number of edges
void dfs(int cur, int compId, unordered_map<int, vector<int>>& adj, vector<int>& component) {
    component[cur] = compId;
    
    for (int& ngbr : adj[cur]) {
        if (component[ngbr] == -1) {
            dfs(ngbr, compId, adj, component);
        }
    }
}

vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    unordered_map<int, vector<int>> adj;
    
    for (int i = 0; i + 1 < n; i++) {
        if (nums[i + 1] - nums[i] <= maxDiff) {
            adj[i].push_back(i + 1);
            adj[i + 1].push_back(i);
        }
    }
    
    vector<int> component(n, -1);
    int compId = 0;
    
    for (int i = 0; i < n; i++) {
        if (component[i] == -1) {
            dfs(i, compId, adj, component);
            compId++;
        }
    }
    
    vector<bool> result;
    for (auto& query : queries) {
        result.push_back(component[query[0]] == component[query[1]]);
    }
    
    return result;
}

// Approach - 3 (Using Union-Find / Disjoint Set Union) - Efficient
// T.C : O(n + q * α(n)), where α(n) is the inverse
// S.C : O(n)
int find(vector<int>& parent, int a) {
    if (parent[a] != a) {
        parent[a] = find(parent, parent[a]); // Path compression
    }
    return parent[a];
}

void Union(vector<int>& parent, vector<int>& rank, int a, int b){
    int rootA = find(parent, a);
    int rootB = find(parent, b);
    
    if (rootA != rootB) {
        if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
}

vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    vector<bool> result;
    vector<int> parent(n);
    vector<int> rank(n, 0);
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i + 1 < n; i++) {
        if (nums[i + 1] - nums[i] <= maxDiff) {
            Union(parent, rank, i, i + 1); // Union the nodes if the absolute difference is within maxDiff
        }
    }

    for (auto &query : queries) {
        int u = query[0];
        int v = query[1];
        result.push_back(find(parent, u) == find(parent, v)); // Check if u and v are in the same connected component
    }

    return result;
}

//Approach - 4 (Simple observation - assign components)
//T.C : O(n+q)
//S.C : O(n)
vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    vector<int> component(n, -1);

    int componentId = 0;
    component[0] = componentId;

    for (int i = 1; i < n; i++) {
        if (nums[i] - nums[i - 1] > maxDiff) {
            componentId++;
        }
        component[i] = componentId;
    }

    vector<bool> result;
    for (auto &query : queries) {
        int u = query[0];
        int v = query[1];
        result.push_back(component[u] == component[v]); // Check if u and v are in the same connected component
    }
    return result;
}

int main() {
    int n = 4;
    vector<int> nums = {2, 5, 6, 8};
    int maxDiff = 2;
    vector<vector<int>> queries = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    
    vector<bool> result = pathExistenceQueries(n, nums, maxDiff, queries);
    
    for (bool res : result) {
        cout << (res ? "true" : "false") << " "; // Output the results of the queries
    }
    
    return 0;
}