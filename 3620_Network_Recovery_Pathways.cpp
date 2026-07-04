/*
Network Recovery Pathways - [Leetcode - 3620(Hard)]
-------------------------------------------------------

You are given a directed acyclic graph of n nodes numbered from 0 to n − 1. This is represented by a 2D array edges of length m, where edges[i] = [ui, vi, costi] indicates a one‑way communication from node ui to node vi with a recovery cost of costi.

Some nodes may be offline. You are given a boolean array online where online[i] = true means node i is online. Nodes 0 and n − 1 are always online.

A path from 0 to n − 1 is valid if:

All intermediate nodes on the path are online.
The total recovery cost of all edges on the path does not exceed k.
For each valid path, define its score as the minimum edge‑cost along that path.

Return the maximum path score (i.e., the largest minimum-edge cost) among all valid paths. If no valid path exists, return -1.

Example 1:

Input: edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [true,true,true,true], k = 10

Output: 3

Explanation:

The graph has two possible routes from node 0 to node 3:

Path 0 → 1 → 3

Total cost = 5 + 10 = 15, which exceeds k (15 > 10), so this path is invalid.

Path 0 → 2 → 3

Total cost = 3 + 4 = 7 <= k, so this path is valid.

The minimum edge‐cost along this path is min(3, 4) = 3.

There are no other valid paths. Hence, the maximum among all valid path‐scores is 3.

Example 2:

Input: edges = [[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]], online = [true,true,true,false,true], k = 12

Output: 6

Explanation:

Node 3 is offline, so any path passing through 3 is invalid.

Consider the remaining routes from 0 to 4:

Path 0 → 1 → 4

Total cost = 7 + 5 = 12 <= k, so this path is valid.

The minimum edge‐cost along this path is min(7, 5) = 5.

Path 0 → 2 → 3 → 4

Node 3 is offline, so this path is invalid regardless of cost.

Path 0 → 2 → 4

Total cost = 6 + 6 = 12 <= k, so this path is valid.

The minimum edge‐cost along this path is min(6, 6) = 6.

Among the two valid paths, their scores are 5 and 6. Therefore, the answer is 6.

 

Constraints:

n == online.length
2 <= n <= 5 * 10^4
0 <= m == edges.length <= min(105, n * (n - 1) / 2)
edges[i] = [ui, vi, costi]
0 <= ui, vi < n
ui != vi
0 <= costi <= 10^9
0 <= k <= 5 * 10^13
online[i] is either true or false, and both online[0] and online[n − 1] are true.
The given graph is a directed acyclic graph.
*/

// BINARY SEARCH ON ANSWER + DIJKSTRA'S ALGORITHM

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <algorithm>
using namespace std;

#define ll long long

// Dijkstra's algorithm
bool check(int midScore, int n,  ll k, vector<vector<pair<int, int>>>& graph) {
    // result[i] = minimum cost path from source to ith node
    vector<ll> result(n, LLONG_MAX);

    // MIN-HEAP -> Dijkstra's algorithm
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq; // {cost, node}
    
    result[0] = 0; // cost to reach source node is 0
    pq.push({0, 0}); // start from node 0 with cost 0

    while(!pq.empty()){
        ll d = pq.top().first; // current cost
        int node = pq.top().second; // current node
        pq.pop();

        if(d > k) return false; // if current cost exceeds k, no need to proceed

        if(node == n - 1) return true; // reached destination node

        // total cost reaching from source to node = d
        if(d > result[node]) continue; // if current cost is greater than already found minimum cost, skip

        for(auto &edge : graph[node]){
            int neighbour = edge.first;
            int edgeCost = edge.second;

            if(edgeCost < midScore) continue; // skip edges with cost less than midScore
            if(result[neighbour] > d + edgeCost){
                result[neighbour] = d + edgeCost; // update minimum cost to reach neighbour
                pq.push({result[neighbour], neighbour}); // push neighbour into priority queue
            }
        }
    }

    return false; // if destination node is not reachable within cost k
}

int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
    int n = online.size(); // total n nodes

    int low = INT_MAX;
    int high = 0;
    
    // Graph representation using adjacency list
    vector<vector<pair<int, int>>> graph(n); // u -> {(v, cost), (v', cost'), ...}
    for(auto &edge : edges){
        int u = edge[0];
        int v = edge[1];
        int cost = edge[2];

        if(!online[u] || !online[v]) continue; // skip if either node is offline
        graph[u].push_back({v, cost});

        low = min(low, cost);
        high = max(high, cost);
    }

    int answer = -1; // Initialize answer to -1 (no valid path found yet)
    
    // Binary Search on the answer -> answer : the minimum edge cost along the path
    while(low <= high){
        int mid = low + (high - low) / 2; // mid score

        if(check(mid, n, k, graph)){
            answer = mid; // valid path found with score >= mid
            low = mid + 1; // try for a higher score
        } else {
            high = mid - 1; // try for a lower score
        }

    }
    return answer;
}

int main() {
    vector<vector<int>> edges = {{0,1,5},{1,3,10},{0,2,3},{2,3,4}};
    vector<bool> online = {true,true,true,true};
    long long k = 10;

    int result = findMaxPathScore(edges, online, k);
    cout << "Maximum Path Score: " << result << endl; // Output: 3

    return 0;
}