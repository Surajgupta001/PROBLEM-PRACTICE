/*
Rotating the Box - [Leetcode - 1861(Medium)]
----------------------------------------------
You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

Example 1:

Input: boxGrid = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]

Example 2:

Input: boxGrid = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]

Example 3:

Input: boxGrid = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]
 

Constraints:

m == boxGrid.length
n == boxGrid[i].length
1 <= m, n <= 500
boxGrid[i][j] is either '#', '*', or '.'.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Approach-1 (Brute Force)
//T.C : O(col * row * row)
//S.C : O(1) - Not considering the space of result
vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
    int m = box.size();
    int n = box[0].size();
    
    vector<vector<char>> result(n, vector<char>(m));
    
    //Transpose
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            result[i][j] = box[j][i];
        }
    }
    
    //90 degree k lie - Reverse kardo ahr row ko
    for(vector<char>& row : result) {
        reverse(begin(row), end(row));
    }
    
    //Apply the gravity
    for(int j = 0; j < m; j++) {
        for(int i = n-1; i >= 0; i--) {
            if(result[i][j] == '.') { //if it is a space
                int stoneRow = -1;
                for(int k = i-1; k >= 0; k--) {
                    if(result[k][j] == '*') {
                        break;
                    } else if(result[k][j] == '#') {
                        stoneRow = k;
                        break;
                    }
                }
                if(stoneRow != -1) {
                    result[i][j] = '#';
                    result[stoneRow][j] = '.';
                }
            }
        }
    }
    
    return result;
}

//Approach-2 (Optimized)
//T.C : O(col * row)
//S.C : O(1) - Not considering the space of result
vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
    int m = box.size();
    int n = box[0].size();
    
    vector<vector<char>> result(n, vector<char>(m));
    
    //Transpose
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            result[i][j] = box[j][i];
        }
    }
    
    //90 degree k lie - Reverse kardo ahr row ko
    for(vector<char>& row : result) {
        reverse(begin(row), end(row));
    }
    
    //Apply the gravity
    //O(col * row)
    for(int j = 0; j < m; j++) {
        int spaceBottomRow = n-1;
        for(int i = n-1; i >= 0; i--) {
            if(result[i][j] == '*') {
                spaceBottomRow = i-1;
                continue;
            }
            if(result[i][j] == '#') {
                result[i][j] = '.';
                result[spaceBottomRow][j] = '#';
                spaceBottomRow--;
            }
        }
    }
    
    return result;
}

int main() {
    vector<vector<char>> boxGrid = {
        {'#', '.', '*', '.'},
        {'#', '#', '*', '.'}
    };

    vector<vector<char>> result = rotateTheBox(boxGrid);

    for (const auto& row : result) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}