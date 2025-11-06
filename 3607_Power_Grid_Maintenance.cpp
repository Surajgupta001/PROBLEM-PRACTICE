/*
Power Grid Maintenance - [Leetcode - 3607(Medium)]
----------------------------------------------------
You are given an integer c representing c power stations, each with a unique identifier id from 1 to c (1‑based indexing).

These stations are interconnected via n bidirectional cables, represented by a 2D array connections, where each element connections[i] = [ui, vi] indicates a connection between station ui and station vi. Stations that are directly or indirectly connected form a power grid.

Initially, all stations are online (operational).

You are also given a 2D array queries, where each query is one of the following two types:

[1, x]: A maintenance check is requested for station x. If station x is online, it resolves the check by itself. If station x is offline, the check is resolved by the operational station with the smallest id in the same power grid as x. If no operational station exists in that grid, return -1.

[2, x]: Station x goes offline (i.e., it becomes non-operational).

Return an array of integers representing the results of each query of type [1, x] in the order they appear.

Note: The power grid preserves its structure; an offline (non‑operational) node remains part of its grid and taking it offline does not alter connectivity.

 

Example 1:

Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]

Output: [3,2,3]

Explanation:



Initially, all stations {1, 2, 3, 4, 5} are online and form a single power grid.
Query [1,3]: Station 3 is online, so the maintenance check is resolved by station 3.
Query [2,1]: Station 1 goes offline. The remaining online stations are {2, 3, 4, 5}.
Query [1,1]: Station 1 is offline, so the check is resolved by the operational station with the smallest id among {2, 3, 4, 5}, which is station 2.
Query [2,2]: Station 2 goes offline. The remaining online stations are {3, 4, 5}.
Query [1,2]: Station 2 is offline, so the check is resolved by the operational station with the smallest id among {3, 4, 5}, which is station 3.
Example 2:

Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]

Output: [1,-1]

Explanation:

There are no connections, so each station is its own isolated grid.
Query [1,1]: Station 1 is online in its isolated grid, so the maintenance check is resolved by station 1.
Query [2,1]: Station 1 goes offline.
Query [1,1]: Station 1 is offline and there are no other stations in its grid, so the result is -1.
 

Constraints:

1 <= c <= 105
0 <= n == connections.length <= min(105, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 10^5
queries[i].length == 2
queries[i][0] is either 1 or 2.
1 <= queries[i][1] <= c
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// Approach : 1 - Brute Force (DFS)
void dfs(int node, unordered_map<int, vector<int>> &graph, vector<bool> &visited, vector<int> &nodeId, int id, unordered_map<int, set<int>> &componentStations, const vector<bool> &online){
    visited[node] = true;
    nodeId[node] = id; // Assign component id to node
    if(online[node]){
        componentStations[id].insert(node); // Add station to its component's set if it's online
    }

    for(int neighbor : graph[node]){
        if(!visited[neighbor]){
            dfs(neighbor, graph, visited, nodeId, id, componentStations, online);
        }
    }
}

vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
    unordered_map<int, vector<int>> graph;
    
    // Build Graph
    for(auto &edge : connections){
        int u = edge[0];
        int v = edge[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(c + 1, false); // for DFS visitation
    vector<bool> online(c + 1, true);   // All stations are initially online
    vector<int> nodeId(c + 1, 0); // To store component id for each node
    unordered_map<int, set<int>> componentStations; // component_id -> set of online stations in that component

    for(int node = 1; node <= c; ++node){
        if(!visited[node]){
            int id = node; // Use node as component id
            dfs(node, graph, visited, nodeId, id, componentStations, online);
        }
    }

    vector<int> results; // To store results of type 1 queries
    for(auto &query : queries){
        int type = query[0];
        int node = query[1];

        if(type == 1){
            // Maintenance check
            if(online[node]){
                results.push_back(node); // Station is online
            }
            else{
                int compId = nodeId[node];
                if(compId != 0 && !componentStations[compId].empty()){
                    results.push_back(*componentStations[compId].begin()); // Smallest id online station in the component
                }
                else{
                    results.push_back(-1); // No online stations in the component
                }
            }
        }
        else if(type == 2){
            // Take station offline
            if(online[node]){
                int compId = nodeId[node];
                if(compId != 0){
                    componentStations[compId].erase(node);
                }
                online[node] = false;
            }
        }
    }

    return results;
}

// Approach - 2 - Union Find (Disjoint Set Union - DSU) with additional data structures
int find(vector<int>& parent, int x){
    return parent[x] == x ? x : parent[x] = find(parent, parent[x]);
}

void Union(vector<int>& parent, vector<int>& rank, int a, int b){
    // Union by rank
    a = find(parent, a);
    b = find(parent, b);
    if (a == b) return;
    if (rank[a] < rank[b]) swap(a, b);
    parent[b] = a;
    if (rank[a] == rank[b]) rank[a]++;
}

vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
    // 1) Build DSU for the fixed grid connectivity
    vector<int> parent(c + 1);
    vector<int> rank(c + 1, 0);
    for (int i = 1; i <= c; ++i){
        parent[i] = i;
    }
    for (auto& e : connections){
        Union(parent, rank, e[0], e[1]);
    }

    // 2) Build per-component set of online stations (initially all online)
    vector<set<int>> onlineSet(c + 1);
    vector<char> online(c + 1, 1);
    for (int i = 1; i <= c; ++i) {
        int r = find(parent, i);
        onlineSet[r].insert(i);
    }

    // 3) Answer queries
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
        int type = q[0];
        int x = q[1];
        int r = find(parent, x);

        if (type == 1) {
            if (online[x]) {
                ans.push_back(x);
            } else {
                // Get smallest online station in x's component (if any)
                if (onlineSet[r].empty()) ans.push_back(-1);
                else ans.push_back(*onlineSet[r].begin());
            }
        } else { // type == 2: take x offline
            if (online[x]) {
                online[x] = 0;
                // Remove from its component's online set
                onlineSet[r].erase(x);
            }
        }
    }
    return ans;
}

int main() {
    int c = 5;
    vector<vector<int>> connections = {{1,2},{2,3},{3,4},{4,5}};
    vector<vector<int>> queries = {{1,3},{2,1},{1,1},{2,2},{1,2}};

    vector<int> results = processQueries(c, connections, queries);

    for(int res : results){
        cout << res << " ";
    }
    cout << endl;

    return 0;
}