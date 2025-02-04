/*
Convert an Array Into a 2D Array With Conditions - [Leetcode - 2160(Medium)]
================================================================================
You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:

=> The 2D array should contain only the elements of the array nums.
=> Each row in the 2D array contains distinct integers.
=> The number of rows in the 2D array should be minimal.
Return the resulting array. If there are multiple answers, return any of them.

Note that the 2D array can have a different number of elements on each row.


Example 1:

Input: nums = [1,3,4,1,2,3,1]
Output: [[1,3,4,2],[1,3],[1]]
Explanation: We can create a 2D array that contains the following rows:
- 1,3,4,2
- 1,3
- 1
All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
It can be shown that we cannot have less than 3 rows in a valid array.

Example 2:

Input: nums = [1,2,3,4]
Output: [[4,3,2,1]]
Explanation: All elements of the array are distinct, so we can keep all of them in the first row of the 2D array.
*/ 

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> findMatrix(vector<int>& v) {
    vector<vector<int>> ans;
    for (int num : v) {
        bool added = false;
        // Try to add the number to an existing row
        for (auto& row : ans) {
            if (find(row.begin(), row.end(), num) == row.end()) {
                row.push_back(num);
                added = true;
                break;
            }
        }
        // If the number couldn't be added to any existing row, create a new row
        if (!added) ans.push_back({num});
    }
    return ans;
}

int main() {

    int n;
    cout << "Enter the size of vector: ";
    cin >> n;

    vector<int> v(n);
    cout << "Enter the elements of vector: ";
    for (int i = 0; i < n; i++) cin >> v[i];

    vector<vector<int>> ans = findMatrix(v);
    cout << "Output: " << endl;
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// vector<vector<int>> findMatrix(vector<int>& v){
//     vector<int>freq(201,0);
//     vector<vector<int>> ans;
//     for(auto c : v){
//         if(freq[c] == ans.size()) ans.push_back({});
//         ans[freq[c]++].push_back(c);
//     }
//     return ans;
// }