/*
Pascal's Triangle - [LeetCode - 118(Easy)]
-------------------------------------------
Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Example 2:

Input: numRows = 1
Output: [[1]]
 

Constraints:

1 <= numRows <= 30
*/ 

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans(numRows);
    for (int i = 0; i < numRows; ++i) {
        ans[i] = vector<int>(i + 1, 1); // Initialize with 1s
        for (int j = 1; j < i; ++j) {
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j]; // Fill in the values based on the previous row
        }
    }
    return ans;
}

int main() {
    cout << "Starting Pascal's Triangle generation..." << endl;
    int numRows = 5;
    vector<vector<int>> result = generate(numRows);
    cout << "Generated triangle with " << result.size() << " rows:" << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "Program completed." << endl;
    return 0;
}