/*
Number of Equivalent Domino Pairs - [Leetcode - 1128(Easy)]
-----------------------------------------------------------
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].

Example 1:

Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1

Example 2:

Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
Output: 3
 

Constraints:

1 <= dominoes.length <= 4 * 104
dominoes[i].length == 2
1 <= dominoes[i][j] <= 9
*/ 

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Brute Force Approach
// Time Complexity: O(n^2) - where n is the number of dominoes
int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    int n = dominoes.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((dominoes[i][0] == dominoes[j][0] and dominoes[i][1] == dominoes[j][1]) or (dominoes[i][0] == dominoes[j][1] and dominoes[i][1] == dominoes[j][0])) {
                count++;
            }
        }
    }
    return count;
}

// Optimized Approach using HashMap
// Time Complexity: O(n) - where n is the number of dominoes
// Space Complexity: O(n) - to store the frequency of each domino pair
int numEquivDominoPairs(vector<vector<int>>& dominoes){
    int count= 0;

    map<pair<int,int>, int> mp; // to store the frequency of each domino pair

    for(int i=0; i<dominoes.size(); i++){
        if(dominoes[i][0] > dominoes[i][1]){
            swap(dominoes[i][0], dominoes[i][1]); // ensure the smaller number is first i.e. (2,1) --> (1,2)
        }

        mp[{dominoes[i][0], dominoes[i][1]}]++; // increment the frequency of the pair
    }

    for(auto &itr : mp){
        int freq = itr.second; // frequency of the current pair
        count += (freq * (freq - 1)) / 2; // calculate the number of pairs for this frequency
    }

    return count; // return the total count of equivalent domino pairs
}

// Approach 3: Using Constant Space
// Time Complexity: O(n) - where n is the number of dominoes
// Space Complexity: O(1) - since we are using a fixed size array of size 100
int numEquivDominoPairs(vector<vector<int>>& dominoes){
    int count = 0;

    vector<int> v(100);
    for(auto &d : dominoes){
        if(d[0] > d[1]){
            swap(d[0], d[1]); // ensure the smaller number is first i.e. (2,1) --> (1,2)
        }

        int num = (d[0] * 10) + d[1]; // convert the pair to a single number
        
        count += v[num]; // add the frequency of the current pair to the count
        
        v[num]++; // increment the frequency of the converted number
    }

    return count;
}

int main(){
        
    vector<vector<int>> dominoes = {{1,2},{2,1},{3,4},{5,6}};
    cout << numEquivDominoPairs(dominoes) << endl;

    vector<vector<int>> dominoes2 = {{1,2},{1,2},{1,1},{1,2},{2,2}};
    cout << numEquivDominoPairs(dominoes2) << endl;
    

    vector<vector<int>> dominoes3 = {{1,3},{3,1},{2,2},{2,1},{1,2}};
    cout << numEquivDominoPairs(dominoes3) << endl;
    
    return 0;
}