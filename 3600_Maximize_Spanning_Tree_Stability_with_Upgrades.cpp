/*
Maximize Spanning Tree Stability with Upgrades - [Leetcode - 3600(Hard)]
----------------------------------------------------------------------------
You are given an integer n, representing n nodes numbered from 0 to n - 1 and a list of edges, where edges[i] = [ui, vi, si, musti]:

• ui and vi indicates an undirected edge between nodes ui and vi.
• si is the strength of the edge.
• musti is an integer (0 or 1). If musti == 1, the edge must be included in the spanning tree. These edges cannot be upgraded.
You are also given an integer k, the maximum number of upgrades you can perform. Each upgrade doubles the strength of an edge, and each eligible edge (with musti == 0) can be upgraded at most once.

The stability of a spanning tree is defined as the minimum strength score among all edges included in it.

Return the maximum possible stability of any valid spanning tree. If it is impossible to connect all nodes, return -1.

Note: A spanning tree of a graph with n nodes is a subset of the edges that connects all nodes together (i.e. the graph is connected) without forming any cycles, and uses exactly n - 1 edges.

Example 1:

Input: n = 3, edges = [[0,1,2,1],[1,2,3,0]], k = 1

Output: 2

Explanation:
• Edge [0,1] with strength = 2 must be included in the spanning tree.
• Edge [1,2] is optional and can be upgraded from 3 to 6 using one upgrade.
• The resulting spanning tree includes these two edges with strengths 2 and 6.
• The minimum strength in the spanning tree is 2, which is the maximum possible stability.

Example 2:

Input: n = 3, edges = [[0,1,4,0],[1,2,3,0],[0,2,1,0]], k = 2

Output: 6

Explanation:
• Since all edges are optional and up to k = 2 upgrades are allowed.
• Upgrade edges [0,1] from 4 to 8 and [1,2] from 3 to 6.
• The resulting spanning tree includes these two edges with strengths 8 and 6.
• The minimum strength in the tree is 6, which is the maximum possible stability.

Example 3:

Input: n = 3, edges = [[0,1,1,1],[1,2,1,1],[2,0,1,1]], k = 0

Output: -1

Explanation:

All edges are mandatory and form a cycle, which violates the spanning tree property of acyclicity. Thus, the answer is -1.
 

Constraints:

• 2 <= n <= 10^5
• 1 <= edges.length <= 10^5
• edges[i] = [ui, vi, si, musti]
• 0 <= ui, vi < n
• ui != vi
• 1 <= si <= 10^5
• musti is either 0 or 1.
• 0 <= k <= n
• There are no duplicate edges.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Forward declarations for DSU functions so check() can use them
int find(vector<int>& parent, int x);
void Union(vector<int>& parent, vector<int>& rank, int a, int b);

// Helper function to check if we can form a valid spanning tree 
// where the minimum edge strength (stability) is AT LEAST 'mid'.
bool check (int n, vector<vector<int>>& edges, int mid, int k) {
    // 1. Create a fresh Disjoint Set Union (DSU) for this specific 'mid' check.
    vector<int> parent(n), rank(n, 0);
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }

    // This will hold optional edges that are currently too weak (< mid) 
    // but CAN reach >= mid if we use exactly ONE upgrade.
    vector<vector<int>> upgradeCandidates; 

    // 2. First Pass: Process mandatory edges and naturally strong optional edges
    for(auto &edge : edges){
        int u = edge[0], v = edge[1], s = edge[2], m = edge[3];

        if(m == 1){ 
            // Mandatory Edge
            // Since we CANNOT upgrade mandatory edges, if its strength is less 
            // than our target 'mid', our target is impossible.
            if(s < mid) return false;
            Union(parent, rank, u, v); 
        } else {
            // Optional Edge
            if(s >= mid){
                // This edge is already strong enough to meet our target stability 'mid'
                // without wasting an upgrade. 
                Union(parent, rank, u, v); 
            } else if(s * 2 >= mid){
                // This edge falls short naturally, BUT if we double it, it hits 'mid'.
                // We don't merge it yet; we save it for later in case we need it 
                // to connect components and we have spare upgrades (k).
                upgradeCandidates.push_back(edge); 
            }
        }
    }

    // 3. Second Pass: Process our upgrade candidates
    // We only use upgrades if we absolutely have to (i.e., the nodes are not yet connected).
    for(auto &edge : upgradeCandidates){
        int u = edge[0], v = edge[1];
        
        // If 'u' and 'v' are NOT in the same component, we need an edge to connect them.
        if(find(parent, u) != find(parent, v)){ 
            if(k <= 0) continue; // We have no upgrades left, skip trying to use this edge.
            
            // We have an upgrade available. Use it to connect 'u' and 'v'.
            Union(parent, rank, u, v); 
            k--; // Deduct one upgrade
        }
    }

    // 4. Connectivity Check
    // A valid spanning tree MUST connect ALL nodes into a single component.
    int root = find(parent, 0); 
    for (int node = 1; node < n; node++) {
        // If any node's overall parent differs from node 0's parent, the graph is disconnected.
        if (find(parent, node) != root) { 
            return false; 
        }
    }
    
    // If we made it here, everything is connected and no conditions were violated!
    return true; 
}

// Standard Disjoint Set Union (DSU) - Find with path compression
int find(vector<int>& parent, int x) {
    // Finds the representative (root) of the set that 'x' belongs to.
    return parent[x] = (parent[x] == x) ? x : find(parent, parent[x]);
}

// Standard Disjoint Set Union (DSU) - Union by rank
void Union(vector<int>& parent, vector<int>& rank, int a, int b) {
    // Merges the clusters containing 'a' and 'b'.
    a = find(parent, a);
    b = find(parent, b);

    if(a != b) { 
        if(rank[a] >= rank[b]){
            rank[a]++;
            parent[b] = a;
        }
        else{
            rank[b]++;
            parent[a] = b;
        }
    }
}

int maxStability(int n, vector<vector<int>>& edges, int k) {
    // Phase 1: Pre-Validation Check
    // If the mandatory edges ALONE form a cycle, it's immediately impossible 
    // to form a valid spanning tree because trees cannot have cycles.
    vector<int> parent(n), rank(n, 0);
    for(int i = 0; i < n; i++) parent[i] = i;

    for(auto &edge : edges){
        if(edge[3] == 1){ // must include
            if(find(parent, edge[0]) == find(parent, edge[1])){
                return -1; // Mandatory edges form a cycle, spanning tree impossible
            }
            Union(parent, rank, edge[0], edge[1]);
        }
    }

    int result = -1;
    
    // Phase 2: Binary Search on Answer
    // We are looking for the MAXIMUM possible minimum strength (stability).
    // Lowest possible strength is 1. Highest possible is 2 * 10^5 (max edge * 2).
    int low = 1;
    int high = 2 * 1e5; 

    while(low <= high){
        int mid = low + (high - low) / 2; // 'mid' is our guessed target stability

        // If we can successfully build a tree with minimum stability 'mid'...
        if(check(n, edges, mid, k)){ 
            result = mid;   // Remember this valid stability
            low = mid + 1;  // Try to push for an even HIGHER stability
        }
        else{
            // We failed to build a tree with 'mid' stability.
            // It's too strict, so we must lower our target stability.
            high = mid - 1; 
        }
    }
    
    return result;
}

int main () {
    int n = 3;
    vector<vector<int>> edges = {{0,1,2,1},{1,2,3,0}};
    int k = 1;
    cout << maxStability(n, edges, k) << endl; // Output: 2

    n = 3;
    edges = {{0,1,4,0},{1,2,3,0},{0,2,1,0}};
    k = 2;
    cout << maxStability(n, edges, k) << endl; // Output: 6

    n = 3;
    edges = {{0,1,1,1},{1,2,1,1},{2,0,1,1}};
    k = 0;
    cout << maxStability(n, edges, k) << endl; // Output: -1

    return 0;
}