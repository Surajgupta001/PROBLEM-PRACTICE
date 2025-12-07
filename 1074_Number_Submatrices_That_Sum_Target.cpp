/*
Number of Submatrices That Sum to Target - [Leetcode - 1074(Hard)]
--------------------------------------------------------------------
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

Example 1:

Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Example 2:

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
Example 3:

Input: matrix = [[904]], target = 0
Output: 0
 
Constraints:

1 <= matrix.length <= 100
1 <= matrix[0].length <= 100
-1000 <= matrix[i][j] <= 1000
-10^8 <= target <= 10^8
*/ 

// ============= Firstly solve - [Leetcode - 560(medium)] =============

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force Approach
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int count = 0;

    for (int sr = 0; sr < rows; sr++) {              // starting row
        for (int sc = 0; sc < cols; sc++) {          // starting col
            for (int er = sr; er < rows; er++) {     // ending row
                for (int ec = sc; ec < cols; ec++) { // ending col
                    int sum = 0;
                    for (int i = sr; i <= er; i++) {
                        for (int j = sc; j <= ec; j++) {
                            sum += matrix[i][j];
                        }
                    }
                    if (sum == target) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

// Optimized Approach
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Firstly take row wise cummulative sum
    for(int row=0; row<rows; row++){
        for(int col=1; col<cols; col++){
            matrix[row][col] += matrix[row][col-1]; // cummulative sum row wise
        }
    }

    // Now, we need to find the number of subarrays with sum equal to target for each pair of columns => in downwards directions - [Leetcode - 560]
    int result = 0;
    for(int startCol=0; startCol<cols; startCol++){
        for(int j=startCol; j<cols; j++){
            unordered_map<int, int> mp; //prefix sum and its frequency
            
            mp.insert({0,1});

            int currSum = 0;
            for(int row=0; row<rows; row++){
                currSum += matrix[row][j] - (startCol > 0 ? matrix[row][startCol - 1] : 0);
                if(mp.count(currSum - target)){
                    result += mp[currSum - target];
                }
                mp[currSum]++;
            }
        }
    }
    return result;
}

int main() {
    vector<vector<int>> matrix = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    int target = 0;
    cout << "Number of submatrices that sum to target " << target << ": " << numSubmatrixSumTarget(matrix, target) << endl;
    return 0;
}