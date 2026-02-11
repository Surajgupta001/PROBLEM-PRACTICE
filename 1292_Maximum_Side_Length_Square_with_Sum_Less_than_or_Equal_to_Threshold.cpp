/*
Maximum Side Length of a Square with Sum Less than or Equal to Threshold - [Leetcode - 1292(Medium)]
------------------------------------------------------------------------------------------------------
Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.

Example 1:

Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.

Example 2:

Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 300
0 <= mat[i][j] <= 10^4
0 <= threshold <= 10^5
*/

#include <iostream>
#include <vector>
using namespace std;

//Approach-1 (Using 2D Prefix Sum and finding best side square)
//T.C : O(rows * cols * min(rows, cols))
//S.C : O(rows * cols)

int maxSideLength(vector<vector<int>>& mat, int threshold) {
    int rows = mat.size();
    int cols = mat[0].size();
    vector<vector<int>> prefix(rows, vector<int>(cols, 0));
    // Build prefix sum
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            prefix[i][j] = mat[i][j]
                         + (i > 0 ? prefix[i - 1][j] : 0)
                         + (j > 0 ? prefix[i][j - 1] : 0)
                         - (i > 0 && j > 0 ? prefix[i - 1][j - 1] : 0);
        }
    }
    // Helper lambda to get sum of square
    auto sumSquare = [&](int i, int j, int r2, int c2) {
        int sum = prefix[r2][c2];
                if (i > 0) sum -= prefix[i - 1][c2];
                if (j > 0) sum -= prefix[r2][j - 1];
                if (i > 0 && j > 0) sum += prefix[i - 1][j - 1];
        
        return sum;
    };
    int best = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = best; k < min(rows - i, cols - j); k++) { //offset to find bottom right cell
                //bottom right cell (r2, c2)
                int r2 = i + k;
                int c2 = j + k;
                int sum = sumSquare(i, j, r2, c2);
                if (sum <= threshold) {
                    best = k + 1; //(offset + 1) gives the side of square
                } else {
                    break; //because sum will increase only. Better move to next cell
                }
            }
        }
    }
    return best;
}



//Approach-2 (Using 2D Prefix Sum and binarysearch the square side)
//T.C : O(rows * cols * log(min(rows, cols)))
//S.C : O(rows * cols)
int maxSideLength(vector<vector<int>>& mat, int threshold) {
    int rows = mat.size();
    int cols = mat[0].size();
    // Build prefix sum
    vector<vector<int>> prefix(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            prefix[i][j] = mat[i][j]
                         + (i > 0 ? prefix[i - 1][j] : 0)
                         + (j > 0 ? prefix[i][j - 1] : 0)
                         - (i > 0 && j > 0 ? prefix[i - 1][j - 1] : 0);
        }
    }
    // Sum of square (r1,c1) -> (r2,c2)
    auto sumSquare = [&](int r1, int c1, int r2, int c2) {
        int sum = prefix[r2][c2];
        if (r1 > 0) sum -= prefix[r1 - 1][c2];
        if (c1 > 0) sum -= prefix[r2][c1 - 1];
        if (r1 > 0 && c1 > 0) sum += prefix[r1 - 1][c1 - 1];
        return sum;
    };
    // Check function
    auto check = [&](int side) {
        for (int i = 0; i + side - 1 < rows; i++) {
            for (int j = 0; j + side - 1 < cols; j++) {
                if (sumSquare(i, j,
                              i + side - 1,
                              j + side - 1) <= threshold) {
                    return true;
                }
            }
        }
        return false;
    };
    // Binary search on side length
    int lo = 1, hi = min(rows, cols);
    int result = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            result = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return result;
}

int main() {
    vector<vector<int>> mat = {
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2}
    };
    
    int threshold = 4;
    
    cout << "Maximum side length: " << maxSideLength(mat, threshold) << endl;
    
    return 0;
}