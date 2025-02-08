/*
Spiral Matrices - [Leetcode - 54(Medium)]
=============================================
Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/ 

#include <iostream>
#include <vector>
using namespace std;

void spiralOrder(vector<vector<int>>& matrix){
    /*
    * Time : O(m * n);
    * Space : O(1);
    */ 
    int left = 0;
    int right = matrix[0].size() - 1; // column
    int top = 0;
    int bottom = matrix.size() - 1; // row

    int dir = 0; // direction
    while(left<=right && top<=bottom){
        if(dir == 0){ // left --> right
            for(int col = left; col <= right; col++){
                cout << matrix[top][col] << " ";
            }
            top++;
        }
        else if(dir == 1){ // top --> bottom
            for(int row = top; row <= bottom; row++){
                cout << matrix[row][right] << " ";
            }
            right--;
        }
        else if(dir == 2){ // right ---> left
            for(int col = right; col >= left; col--){
                cout << matrix[bottom][col] << " ";
            }
            bottom--;
        }
        else if(dir == 3){ // bottom --> top
            for(int row = bottom; row >= top; row--){
                cout << matrix[row][left] << " ";
            }
            left++;
        }
        dir = (dir + 1) % 4; // 0 1 2 3
    }
}

int main(){
    
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    
    spiralOrder(matrix);
    
    return 0;
}