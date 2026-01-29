/*
Minimum Cost to Convert String I - [Leetcode - 2976(Medium)]
-------------------------------------------------------------
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].

You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].

Example 1:

Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.

Example 2:

Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:

Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.
 
Constraints:

1 <= source.length == target.length <= 10^5
source, target consist of lowercase English letters.
1 <= cost.length == original.length == changed.length <= 2000
original[i], changed[i] are lowercase English letters.
1 <= cost[i] <= 10^6
original[i] != changed[i]
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_map>
#include <queue>
using namespace std;

void FloydWarshall(vector<vector<long long>>& adjMatrix, vector<char>& original, vector<char>& changed, vector<int>& cost) {

    // Fill the Adjacency Matrix
    for(int i=0; i<original.size(); i++){
        auto sourceChar = original[i] - 'a';
        auto targetChar = changed[i] - 'a';

        // Fill the cost in adjacency matrix
        adjMatrix[sourceChar][targetChar] = min((long long)cost[i], adjMatrix[sourceChar][targetChar]);
    }

    // Apply Floyd Warshall Algorithm
    for(int k=0; k<26; k++){
        for(int i=0; i<26; i++){
            for(int j=0; j<26; j++){
                adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
            }
        }
    }
}

long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
    vector<vector<long long>> adjMatrix(26, vector<long long>(26, INT_MAX));
    
    FloydWarshall(adjMatrix, original, changed, cost);

    long long totalCost = 0;

    for(int i=0; i<source.length(); i++){
        if(source[i] == target[i]) continue; // No cost if characters are same

        if(adjMatrix[source[i]-'a'][target[i]-'a'] == INT_MAX){ // source[i] - 'a' => that means we are converting char to index 0-25
            return -1; // Impossible to convert
        }

        totalCost += adjMatrix[source[i]-'a'][target[i]-'a'];
    }
    return totalCost;
}

// Dijkstra's Algorithm Approach
void dijkstra(unordered_map<char, vector<pair<char, int>>>& adjMatrix, char &startChar, vector<vector<long long>>& costMatrix) {
    
    // Min-Heap Priority Queue
    priority_queue<pair<long long, char>, vector<pair<long long, char>>, greater<pair<long long, char>>> pq; // (cost, char)
    
    pq.push({0, startChar}); // Starting with 0 cost

    while(!pq.empty()){
        long long d = pq.top().first;
        char adjNode = pq.top().second;
        pq.pop();

        for(auto & neighbor : adjMatrix[adjNode]){
            auto adjNode = neighbor.first;
            auto cost = neighbor.second;

            if(d + cost < costMatrix[startChar - 'a'][adjNode - 'a']){
                costMatrix[startChar - 'a'][adjNode - 'a'] = d + cost;
                pq.push({d + cost, adjNode});
            }
        }
    }

}

long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
    
    // Adjacency List Representation
    unordered_map<char, vector<pair<char, int>>> adjMatrix; // char -> [(char, cost)]

    for(int i=0; i<original.size(); i++){
        adjMatrix[original[i]].push_back({changed[i], cost[i]});
    }

    // Cost Matrix to store min cost from each char to other chars
    vector<vector<long long>> costMatrix(26, vector<long long>(26, INT_MAX));

    // Populate the costMatrix using Dijkstra's Algorithm
    for(int i=0; i<source.length(); i++){
        auto startChar = source[i];

        // Dijkstra's Algorithm
        dijkstra(adjMatrix, startChar, costMatrix);
    }

    long long totalCost = 0;

    for(int i=0; i<source.length(); i++){
        if(source[i] == target[i]) continue; // No cost if characters are same

        if(costMatrix[source[i]-'a'][target[i]-'a'] == INT_MAX){ // source[i] - 'a' => that means we are converting char to index 0-25
            return -1; // Impossible to convert
        }
        
        totalCost += costMatrix[source[i]-'a'][target[i]-'a'];
    }
    
    return totalCost;
}

int main() {
    string source = "abcd";
    string target = "acbe";
    vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'};
    vector<char> changed = {'b', 'c', 'b', 'e', 'b', 'e'};
    vector<int> cost = {2, 5, 5, 1, 2, 20};
    
    long long result = minimumCost(source, target, original, changed, cost);
    cout << "Minimum Cost to Convert String: " << result << endl;

    return 0;
}