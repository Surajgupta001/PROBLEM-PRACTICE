/*
Remove Methods From Project - [Leetcode - 3310(Medium)]
-----------------------------------------------------------
You are maintaining a project that has n methods numbered from 0 to n - 1.

You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.

There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.

A group of methods can only be removed if no method outside the group invokes any methods within it.

Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.

Example 1:

Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]

Output: [0,1,2,3]

Explanation:

Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.

Example 2:

Input: n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]

Output: [3,4]

Explanation:

Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.

Example 3:

Input: n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]

Output: []

Explanation:

All methods are suspicious. We can remove them.

Constraints:

1 <= n <= 10^5
0 <= k <= n - 1
0 <= invocations.length <= 2 * 10^5
invocations[i] == [ai, bi]
0 <= ai, bi <= n - 1
ai != bi
invocations[i] != invocations[j]
*/

// =========== Topological Sorting -> Kahn's Algorithm ===========
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    vector<vector<int>> graph(n);
    vector<int> inDegree(n, 0);
    vector<bool> isSuspicious(n, false);
    // Build the graph and compute in-degrees
    for(auto &edge : invocations){
        int u = edge[0];
        int v = edge[1];

        graph[u].push_back(v);
        inDegree[v]++;
    }

    // Mark suspicious methods using BFS
    queue<int> q;
    q.push(k);
    isSuspicious[k] = true;

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(auto &neighbor : graph[curr]){
            inDegree[neighbor]--;
            if(!isSuspicious[neighbor]){
                q.push(neighbor);
                isSuspicious[neighbor] = true;
            }
        }
    }

    // Check if any suspicious method is invoked by a non-suspicious method
    vector<int> result;
    bool canRemove = true;
    for(int i=0; i<n; i++){
        if(isSuspicious[i] && inDegree[i] > 0){
            // If a suspicious method is invoked by a non-suspicious method, we cannot remove it
            canRemove = false;
            break;
        }
        if(!isSuspicious[i]){
            result.push_back(i);
        }
    }

    if(canRemove){
        vector<int> remaining;
        for(int i=0; i<n; i++){
            if(!isSuspicious[i]){
                remaining.push_back(i);
            }
        }
        return remaining;
    }
    
    return result; // Return empty if we cannot remove suspicious methods
}

int main() {
    int n = 5, k = 0;
    vector<vector<int>> invocations = {{1,2},{0,2},{0,1},{3,4}};
    vector<int> result = remainingMethods(n, k, invocations);
    
    cout << "Remaining Methods: ";
    for(int method : result){
        cout << method << " ";
    }
    cout << endl;

    return 0;
}