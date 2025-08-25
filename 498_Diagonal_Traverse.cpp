/*
Diagonal Traverse - [Leetcode - 498(Medium)]
----------------------------------------------
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

Example 1:


Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]

Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
-105 <= mat[i][j] <= 105
*/ 

// ======== NOTE ========= Similar Problem ======== 1329. Sort the Matrix Diagonally(use - ([i+j])) =======

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    
    map<int, vector<int>> mp;
    //fill the map using [i+j]
    for(int i = 0; i<m; i++) {
        for(int j = 0; j<n; j++) {
            mp[i+j].push_back(mat[i][j]);
        }
    }
    
    vector<int> result;
    bool flip = true;
    for(auto &itr : mp) {
        if(flip) {
            //itr.second ko reverse kardo
            reverse(itr.second.begin(), itr.second.end());
        }
        
        for(auto &num : itr.second) {
            result.push_back(num);
        }
        
        flip = !flip;
    }
    
    return result;
}

int main() {
    vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
    vector<int> result = findDiagonalOrder(mat);
    for(int i : result) {
        cout << i << " ";
    }
    return 0;
}