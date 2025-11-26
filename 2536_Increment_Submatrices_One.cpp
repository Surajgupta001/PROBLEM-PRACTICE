/*
Increment Submatrices by One - [Leetcode - 2536(Medium)]
----------------------------------------------------------
You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.

You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:

Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
Return the matrix mat after performing every query.

Example 1:

Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
Output: [[1,1,0],[1,2,1],[0,1,1]]
Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
- In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
- In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).

Example 2:

Input: n = 2, queries = [[0,0,1,1]]
Output: [[1,1],[1,1]]
Explanation: The diagram above shows the initial matrix and the matrix after the first query.
- In the first query we add 1 to every element in the matrix.

Constraints:

1 <= n <= 500
1 <= queries.length <= 104
0 <= row1i <= row2i < n
0 <= col1i <= col2i < n

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Difference Array Approach
vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries) {
    vector<vector<int>> diff(n, vector<int>(n, 0));
    
    // Same as Difference Array Technique in 1D Array
    
    // Step-1 Process query
    for (auto &query : queries){
        int row1 = query[0];
        int col1 = query[1];
        int row2 = query[2];
        int col2 = query[3];
        
        for (int i = row1; i <= row2; i++){
            diff[i][col1] += 1;
            if (col2 + 1 < n){
                diff[i][col2 + 1] -= 1;
            }
        }
    }
    
    //Step-2 Now calculate prefix sum
    for (int i = 0; i < n; i++){
        for (int j = 1; j < n; j++){
            diff[i][j] += diff[i][j - 1];
        }
    }
    return diff;
}

int main() {
    int n = 3;
    vector<vector<int>> queries = {{1,1,2,2},{0,0,1,1}};

    vector<vector<int>> result = rangeAddQueries(n, queries);

    cout << "Resultant Matrix after all queries: " << endl;
    for(auto &row : result){
        for(auto &val : row){
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}