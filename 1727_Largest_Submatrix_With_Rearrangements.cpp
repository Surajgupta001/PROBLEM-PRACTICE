/*
Largest Submatrix With Rearrangements - [Leetcode - 1727(Medium)]
---------------------------------------------------------------------
You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.

Example 1:
Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.

Example 2:
Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.

Example 3:
Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.
 
Constraints:

m == matrix.length
n == matrix[i].length
1 <= m * n <= 10^5
matrix[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach - Calculate the height of 1's for each column and sort each row in non-increasing order to calculate the area
int largestSubmatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // Strp-1 : Calculate consecutive 1's for each column and store in the same matrix
    for(int i=1; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(matrix[i][j] == 1) {
                matrix[i][j] += matrix[i-1][j];
            }
        }
    }

    int maxArea = 0;

    // Step 2 : Sort each row in non-increasing order and calculate the area
    for(int i=0; i<m; i++){
        sort(matrix[i].begin(), matrix[i].end(), greater<int>());
        for(int j=0; j<n; j++){
            maxArea = max(maxArea, matrix[i][j] * (j+1));
        }
    }

    return maxArea;
}

// Approach - Without modifying the input matrix
int largestSubmatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<vector<int>> height(m, vector<int>(n, 0));

    // Strp-1 : Calculate consecutive 1's for each column and store in the height matrix
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(matrix[i][j] == 1) {
                height[i][j] = (i == 0) ? 1 : height[i-1][j] + 1;
            }
        }
    }

    int maxArea = 0;

    // Step 2 : Sort each row in non-increasing order and calculate the area
    for(int i=0; i<m; i++){
        sort(height[i].begin(), height[i].end(), greater<int>());
        for(int j=0; j<n; j++){
            maxArea = max(maxArea, height[i][j] * (j+1));
        }
    }

    return maxArea;
}

// Without sorting - Using counting sort to calculate the area
int largestSubmatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<vector<int>> height(m, vector<int>(n, 0));

    // Strp-1 : Calculate consecutive 1's for each column and store in the height matrix
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(matrix[i][j] == 1) {
                height[i][j] = (i == 0) ? 1 : height[i-1][j] + 1;
            }
        }
    }

    int maxArea = 0;

    // Step 2 : Calculate the area for each row using counting sort
    for(int i=0; i<m; i++){
        vector<int> count(n+1, 0);
        
        for(int j=0; j<n; j++){
            count[height[i][j]]++;
        }
        
        int currArea = 0;
        
        for(int j=1; j<=n; j++){
            currArea = max(currArea, count[j] * j);
        }
        
        maxArea = max(maxArea, currArea);
    }

    return maxArea;
}

int main() {
    vector<vector<int>> matrix = {{0,0,1},{1,1,1},{1,0,1}};
    cout << largestSubmatrix(matrix) << endl; //Output: 4
    return 0;
}