/*
Minimum Recolors to Get K Consecutive Black Blocks - [Leetcodes - 2379(Easy)]
==============================================================================
You are given a 0-indexed string blocks of length n, where blocks[i] is either 'W' or 'B', representing the color of the ith block. The characters 'W' and 'B' denote the colors white and black, respectively.

You are also given an integer k, which is the desired number of consecutive black blocks.

In one operation, you can recolor a white block such that it becomes a black block.

Return the minimum number of operations needed such that there is at least one occurrence of k consecutive black blocks.

Example 1:

Input: blocks = "WBBWWBBWBW", k = 7
Output: 3
Explanation:
One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
so that blocks = "BBBBBBBWBW". 
It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
Therefore, we return 3.

Example 2:

Input: blocks = "WBWBBBW", k = 2
Output: 0
Explanation:
No changes need to be made, since 2 consecutive black blocks already exist.
Therefore, we return 0.
 

Constraints:

n == blocks.length
1 <= n <= 100
blocks[i] is either 'W' or 'B'.
1 <= k <= n
*/ 

#include <iostream>
#include <string>
#include <climits>
using namespace std;

int minimumRecolors(string blocks, int k) {
    int i = 0; // left pointer
    int j = 0; // right pointer
    int count = 0; // count of white blocks within the window
    int min_operations = INT_MAX; // minimum number of operations

    // Iterate over the string using the j pointer
    while (j < blocks.size()){
        // If the current block is white, increment the count
        if(blocks[j] == 'W'){
            count++;
        }

        // If the window size reaches k
        if (j - i + 1 == k){
            // Update the minimum number of operations
            min_operations = min(min_operations, count);

            // If the leftmost block is white, decrement the count
            if (blocks[i] == 'W') {
                count--;
            }
            // Move the left pointer to the right
            i++;
        }
        // Move the right pointer to the right
        j++;
    }
    return min_operations == INT_MAX ? 0 : min_operations;
}

int main(){
    
    string blocks;
    cout<<"Enter a string: ";
    cin>>blocks;
    
    int k;
    cout<<"Enter the size of the window: ";
    cin>>k;
    
    cout << minimumRecolors(blocks, k) << endl;
    
    return 0;
}