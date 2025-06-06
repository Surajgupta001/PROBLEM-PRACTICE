/*
Lexicographically Smallest Equivalent String - [Leetcode - 1061(MEdium)]
-------------------------------------------------------------------------
You are given two strings of the same length s1 and s2 and a string baseStr.

We say s1[i] and s2[i] are equivalent characters.

For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
Equivalent characters follow the usual rules of any equivalence relation:

Reflexivity: 'a' == 'a'.
Symmetry: 'a' == 'b' implies 'b' == 'a'.
Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab" are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent string of baseStr.

Return the lexicographically smallest equivalent string of baseStr by using the equivalency information from s1 and s2.



Example 1:

Input: s1 = "parker", s2 = "morris", baseStr = "parser"
Output: "makkek"
Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
The characters in each group are equivalent and sorted in lexicographical order.
So the answer is "makkek".

Example 2:

Input: s1 = "hello", s2 = "world", baseStr = "hold"
Output: "hdld"
Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
So only the second letter 'o' in baseStr is changed to 'd', the answer is "hdld".

Example 3:

Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
Output: "aauaaaaada"
Explanation: We group the equivalent characters in s1 and s2 as [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in baseStr except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".


Constraints:

1 <= s1.length, s2.length, baseStr <= 1000
s1.length == s2.length
s1, s2, and baseStr consist of lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

// By using DFS 
char dfsFindMinChar (unordered_map<char, vector<char>>& graph, char curr_Char, vector<int>& visited) {
    visited[curr_Char - 'a'] = 1; // Mark this character as visited

    char minChar = curr_Char; // Initialize minChar with the current character

    for(auto& neighbor : graph[curr_Char]) {
        if(!visited[neighbor - 'a']) { // If neighbor is not visited
            char neighborMinChar = dfsFindMinChar(graph, neighbor, visited);
            minChar = min(minChar, neighborMinChar); // Update minChar with the minimum found
        }
    }
    return minChar; // Return the minimum character found in the connected component
}

// By using BFS
char bfsFindMinChar(unordered_map<char, vector<char>>& graph, char startChar) {
    vector<int> visited(26, 0);
    queue<char> qu;
    char minChar = startChar;

    qu.push(startChar);
    visited[startChar - 'a'] = 1;

    while (!qu.empty()) {
        char curr = qu.front();
        qu.pop();
        minChar = min(minChar, curr);

        for (auto& neighbor : graph[curr]) {
            if (!visited[neighbor - 'a']) {
                visited[neighbor - 'a'] = 1;
                qu.push(neighbor);
            }
        }
    }
    return minChar;
}

int find(vector<int>& parent, int x) {
    // Path compression
    return parent[x] = (parent[x] == x) ? x : find(parent, parent[x]);
}

void Union(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);
    if (a == b) return;
    // Always attach the higher lexicographical root to the lower one
    if (a < b) {
        parent[b] = a;
    }
    else {
        parent[a] = b;
    }
    // Rank is not strictly necessary here, but can be kept for completeness
    if (rank[a] == rank[b]) rank[a]++;
}

// By using DSU
string smallestEquivalentString(string s1, string s2, string baseStr) {
    vector<int> parent(26);
    vector<int> rank(26, 0);
    for (int i = 0; i < 26; ++i) parent[i] = i;

    // Union the equivalence relations
    for (int i = 0; i < s1.size(); ++i) {
        Union(parent, rank, s1[i] - 'a', s2[i] - 'a');
    }

    // Build the result string
    string result;
    for (char ch : baseStr) {
        int root = find(parent, ch - 'a');
        result.push_back('a' + root);
    }
    return result;
}

string smallestEquivalentString(string s1, string s2, string baseStr) {
    int n = s1.size();
    int m = baseStr.size();

    // Build Graph
    unordered_map<char, vector<char>> graph;
    for(int i=0; i<n; i++){
        int u = s1[i];
        int v = s2[i];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    string result;
    for(int i=0; i<m; i++){
        char ch = baseStr[i];

        vector<int> visited(26, 0); // For this ch, none is visited yet
        char minChar = dfsFindMinChar(graph, ch, visited);
        // Alternatively, you can use BFS
        // char minChar = bfsFindMinChar(graph, ch);

        result.push_back(minChar);
    }

    return result;
}



int main () {

    string s1 = "parker", s2 = "morris", baseStr = "parser";
    cout << smallestEquivalentString(s1, s2, baseStr) << endl; // Output: "makkek"

    s1 = "hello", s2 = "world", baseStr = "hold";
    cout << smallestEquivalentString(s1, s2, baseStr) << endl; // Output: "hdld"

    s1 = "leetcode", s2 = "programs", baseStr = "sourcecode";
    cout << smallestEquivalentString(s1, s2, baseStr) << endl; // Output: "aauaaaaada"

    return 0;
}