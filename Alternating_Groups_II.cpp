/*
Alternating Groups II - [Leetcode - 3208(Medium)]
==================================================
There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:

colors[i] == 0 means that tile i is red.
colors[i] == 1 means that tile i is blue.
An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.


Example 1:

Input: colors = [0,1,0,1,0], k = 3

Output: 3

Explanation:

Alternating groups:

Example 2:

Input: colors = [0,1,0,0,1,0,1], k = 6

Output: 2

Explanation:

Alternating groups:

Example 3:

Input: colors = [1,1,0,1], k = 4

Output: 0

Explanation:

Constraints:

3 <= colors.length <= 105
0 <= colors[i] <= 1
3 <= k <= colors.length
*/

#include <iostream>
#include <vector>
using namespace std;

int numberOfAlternatingGroups(vector<int>& colors, int k) {
    int n = colors.size();
    
    int ans = 0;
    int isAlterations = 1; // Initialize isAlterations to 1, assuming the first tile is part of an alternating group

    // Iterate over the vector and the additional k-1 tiles
    for (int i = 1; i < n + k - 1; i++) {
        // Calculate the index of the current tile in the vector
        int j = i % n;
        
        // Check if the current tile is part of an alternating group
        isAlterations = (colors[(i-1) % n] == colors[j]) ? 1 : isAlterations + 1;
        
        // If the alternating group size is greater than or equal to k, increment the answer
        ans += (isAlterations >= k);
    }
    return ans;
}

int main(){

    int n;
    cout << "Enter the size of vector: ";
    cin >> n;

    int k;
    cout << "Enter the size of window: ";
    cin >> k;

    cout << "Enter all the elements of vectors: ";
    vector<int> colors(n);
    for (int i = 0; i < n; i++)
        cin >> colors[i];

    cout << "Number of alternating groups is: " << numberOfAlternatingGroups(colors, k) << endl;

    return 0;
}