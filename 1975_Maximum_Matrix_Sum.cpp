/*
Maximum Matrix Sum - [Leetcode - 1975(Medium)]
------------------------------------------------
You are given an n x n integer matrix. You can do the following operation any number of times:

Choose any two adjacent elements of matrix and multiply each of them by -1.
Two elements are considered adjacent if and only if they share a border.

Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the matrix's elements using the operation mentioned above.

Example 1:

Input: matrix = [[1,-1],[-1,1]]
Output: 4
Explanation: We can follow the following steps to reach sum equals 4:
- Multiply the 2 elements in the first row by -1.
- Multiply the 2 elements in the first column by -1.

Example 2:

Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
Output: 16
Explanation: We can follow the following step to reach sum equals 16:
- Multiply the 2 last elements in the second row by -1.

Constraints:

n == matrix.length == matrix[i].length
2 <= n <= 250
-10^5 <= matrix[i][j] <= 10^5
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

long long maxMatrixSum(vector<vector<int>>& matrix) {
    int m = matrix.size();

    long long absoluteOverallSum = 0;
    int countNegatives = 0;
    int smallestAbsoluteValue = INT_MAX;

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            absoluteOverallSum += abs(matrix[i][j]);

            if(matrix[i][j] < 0){
                countNegatives++;
            }

            smallestAbsoluteValue = min(smallestAbsoluteValue, abs(matrix[i][j]));
        }
    }

    return (countNegatives % 2 == 0) ? absoluteOverallSum : absoluteOverallSum - 2 * smallestAbsoluteValue;
}

int main() {
    vector<vector<int>> matrix1 = {{1, -1}, {-1, 1}};
    cout << "Maximum Matrix Sum (Example 1): " << maxMatrixSum(matrix1) << endl; // Output: 4

    vector<vector<int>> matrix2 = {{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}};
    cout << "Maximum Matrix Sum (Example 2): " << maxMatrixSum(matrix2) << endl; // Output: 16

    return 0;
}