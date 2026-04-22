/*
Minimize Hamming Distance After Swap Operations - [Leetcode - 1722(Medium)]
-----------------------------------------------------------------------------
You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.

Example 1:

Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
Output: 1
Explanation: source can be transformed the following way:
- Swap indices 0 and 1: source = [2,1,3,4]
- Swap indices 2 and 3: source = [2,1,4,3]
The Hamming distance of source and target is 1 as they differ in 1 position: index 3.

Example 2:

Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
Output: 2
Explanation: There are no allowed swaps.
The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.

Example 3:

Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
Output: 0
 

Constraints:

n == source.length == target.length
1 <= n <= 10^5
1 <= source[i], target[i] <= 10^5
0 <= allowedSwaps.length <= 10^5
allowedSwaps[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// DSU -> Using rank and path compression
vector<int> Rank; // To keep track of the rank of each set
vector<int> Parent; // To keep track of the Parent of each element

// Find with path compression
int find(int x) {
    if (Parent[x] != x) {
        Parent[x] = find(Parent[x]); // Path compression
    }
    return Parent[x];
}

void Union(int a, int b){
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB) return; // Already in the same set

    // Union by rank
    if(Rank[rootA] < Rank[rootB]){
        swap(rootA, rootB); // Ensure rootA is the higher rank
    }
    Parent[rootB] = rootA;

    if(Rank[rootA] == Rank[rootB]){
        Rank[rootA]++;
    }
}

int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
    int n = source.size();
    
    Rank.resize(n, 0);
    Parent.resize(n);

    // Initialize parent for each element
    for(int i=0; i<n; i++){
        Parent[i] = i;
    }

    // Union of allowed swaps
    for(auto &vec : allowedSwaps){
        Union(vec[0], vec[1]); // Union the indices based on allowed swaps
    }

    unordered_map<int, unordered_map<int, int>> groupFreq; // Map to count frequency of elements in each group
    for(int i=0; i<n; i++){
        int curr = source[i]; // Current element in source

        int parent = find(i); // Find the parent of the current index
        groupFreq[parent][curr]++; // Increment the frequency of the current element in its group
    }

    // Calculate the minimum Hamming distance
    int hammingDistance = 0;
    for(int i=0; i<n; i++){
        int curr = target[i]; // Current element in target
        int parent = find(i); // Find the parent of the current index

        if(groupFreq[parent].find(curr) != groupFreq[parent].end() && groupFreq[parent][curr] > 0){
            groupFreq[parent][curr]--; // Decrement the frequency of the current element in its group
        } else {
            hammingDistance++; // Increment the Hamming distance if the element is not available in the group
        }
    }

    return hammingDistance;
}

int main() {
    vector<int> source = {1, 2, 3, 4};
    vector<int> target = {2, 1, 4, 5};
    vector<vector<int>> allowedSwaps = {{0, 1}, {2, 3}};

    int result = minimumHammingDistance(source, target, allowedSwaps);
    cout << "Minimum Hamming Distance: " << result << endl; // Output: 1

    return 0;
}