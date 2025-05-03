/*
Minimum Domino Rotations For Equal Row - [Leetcode - 1007(Medium)]
------------------------------------------------------------------

In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.

If it cannot be done, return -1.

Example 1:

Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
Output: 2
Explanation: 
The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.

Example 2:

Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
Output: -1
Explanation: 
In this case, it is not possible to rotate the dominoes to make one row of values equal.
*/ 

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int find(vector<int>& tops, vector<int>& bottoms, int value){

    int swapTops = 0;
    int swapBottoms = 0;

    for(int i=0; i<tops.size(); i++){
        if(tops[i] != value and bottoms[i] != value){
            return -1; // If both values are not equal to the target value, return -1
        }
        else if(tops[i] != value){
            swapTops++; // Count how many swaps are needed in tops
        }
        else if(bottoms[i] != value){
            swapBottoms++; // Count how many swaps are needed in bottoms
        }
    }
    return min(swapTops, swapBottoms);
}

int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
    int ans = INT_MAX;
    
    for(int value = 1; value <= 6; value++) {
        
        int swap = find(tops, bottoms, value);
        
        if(swap != -1){
            ans = min(ans, swap);
        }
    }

    return ans == INT_MAX ? -1 : ans;
}

int main() {
    vector<int> tops = {2, 1, 2, 4, 2, 2};
    vector<int> bottoms = {5, 2, 6, 2, 3, 2};
    
    int result = minDominoRotations(tops, bottoms);
    cout << "Minimum number of rotations: " << result << endl; // Output: 2

    return 0;
}