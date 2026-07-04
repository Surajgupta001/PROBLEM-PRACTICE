/*
Minimum Score of a Path Between Two Cities - [Leetcode - 2492(Medium)]
--------------------------------------------------------------------------

You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.

The score of a path between two cities is defined as the minimum distance of a road in this path.

Return the minimum possible score of a path between cities 1 and n.

Note:

A path is a sequence of roads between two cities.
It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
The test cases are generated such that there is at least one path between 1 and n.

Example 1:

Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
Output: 5
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.

Example 2:

Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
Output: 2
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.

Constraints:

2 <= n <= 10^5
1 <= roads.length <= 10^5
roads[i].length == 3
1 <= ai, bi <= n
ai != bi
1 <= distancei <= 10^4
There are no repeated edges.
There is at least one path between 1 and n.
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void dfs(int u, vector<vector<pair<int, int>>>& graph, vector<bool>& visited, int& result) {
    visited[u] = true;

    // Traverse all neighbors of the current city
    for(auto &neighbor : graph[u]) {
        int v = neighbor.first;
        int distance = neighbor.second;

        // Update the minimum score found so far
        result = min(result, distance);

        if(!visited[v]) {
            dfs(v, graph, visited, result);
        }
    }
}

int minScore(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int, int>>> graph(n + 1); // 1-indexed graph representation

    // Graph representation using adjacency list
    for(auto &road : roads){
        int u = road[0];
        int v = road[1];
        int distance = road[2];
        
        // Undirected graph: add both directions
        graph[u].push_back({v, distance});
        graph[v].push_back({u, distance});
    }

    vector<bool> visited(n + 1, false);
    
    int result = INT_MAX;

    dfs(1, graph, visited, result);

    return result;
}

int main() {
    int n = 4;
    vector<vector<int>> roads = {{1,2,9},{2,3,6},{2,4,5},{1,4,7}};
    
    cout << "Minimum Score of a Path Between Two Cities: " << minScore(n, roads) << endl;

    return 0;
}