/*
Maximum Candies You Can Get from Boxes - [Leetcode - 1298(Hard)]
-----------------------------------------------------------------
You have n boxes labeled from 0 to n - 1. You are given four arrays: status, candies, keys, and containedBoxes where:

=> status[i] is 1 if the ith box is open and 0 if the ith box is closed,
=> candies[i] is the number of candies in the ith box,
=> keys[i] is a list of the labels of the boxes you can open after opening the ith box.
=> containedBoxes[i] is a list of the boxes you found inside the ith box.

You are given an integer array initialBoxes that contains the labels of the boxes you initially have. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.

Return the maximum number of candies you can get following the rules above.

Example 1:

Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
Output: 16
Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2.
Box 1 is closed and you do not have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
Total number of candies collected = 7 + 4 + 5 = 16 candy.

Example 2:

Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
Output: 6
Explanation: You have initially box 0. Opening it you can find boxes 1,2,3,4 and 5 and their keys.
The total number of candies will be 6.
 

Constraints:

n == status.length == candies.length == keys.length == containedBoxes.length
1 <= n <= 1000
status[i] is either 0 or 1.
1 <= candies[i] <= 1000
0 <= keys[i].length <= n
0 <= keys[i][j] < n
All values of keys[i] are unique.
0 <= containedBoxes[i].length <= n
0 <= containedBoxes[i][j] < n
All values of containedBoxes[i] are unique.
Each box is contained in one box at most.
0 <= initialBoxes.length <= n
0 <= initialBoxes[i] < n
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

int dfs(int box, vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes, unordered_set<int>& visited, unordered_set<int>& foundBoxes) {
    if (visited.count(box)) return 0; // If already visited, return 0 candies

    if( status[box] == 0) {
        foundBoxes.insert(box); // If box is closed, add to found boxes
        return 0; // No candies can be collected from a closed box
    }

    visited.insert(box); // Mark the box as visited
    int totalCandies = candies[box]; // Collect candies from the current box

    for(auto &insideBox : containedBoxes[box]) {
        if (visited.count(insideBox) == 0) { // If the inside box has not been visited
            totalCandies += dfs(insideBox, status, candies, keys, containedBoxes, initialBoxes, visited, foundBoxes);
        }
    }

    for(auto &boxKey : keys[box]) {
        if (status[boxKey] == 0) { // If the boxKey opens a closed box
            status[boxKey] = 1; // Mark the box as open
            if (foundBoxes.count(boxKey)) { // If we have found this box before
                totalCandies += dfs(boxKey, status, candies, keys, containedBoxes, initialBoxes, visited, foundBoxes);
            }
        }
    }
    return totalCandies; // Return the total candies collected from this box and its contents
}

int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
    int totalCandies = 0;
    unordered_set<int> visited;
    unordered_set<int> foundBoxes;

    for(auto box : initialBoxes) {
        totalCandies += dfs(box, status, candies, keys, containedBoxes, initialBoxes, visited, foundBoxes);
    }

    /*
    // =========== Using BFS to explore boxes and collect candies =================
    queue<int> qu;
    for(auto box : initialBoxes) { // insert those which you have now and you can open it
        foundBoxes.insert(box); // Mark initial boxes as found
        if(status[box] == 1) { // Only add open boxes to the queue
            qu.push(box);
            visited.insert(box); // Mark the initial box as visited
            totalCandies += candies[box]; // Collect candies from the initial boxes
        }
    }

    while(!qu.empty()) {
        int currentBox = qu.front();
        qu.pop();

        for(auto &insideBox : containedBoxes[currentBox]) {
            foundBoxes.insert(insideBox); // Mark all contained boxes as found
            if(status[insideBox] == 1 && !visited.count(insideBox)) { // If the box is open and not visited
                qu.push(insideBox); // Add to queue for further processing
                visited.insert(insideBox); // Mark as visited
                totalCandies += candies[insideBox]; // Collect candies from this box
            }
                 
        }
        for(auto &boxKey : keys[currentBox]) {
            if(status[boxKey] == 0) { // If the box is closed
                status[boxKey] = 1; // Open the box
                if(foundBoxes.count(boxKey) && !visited.count(boxKey)) { // If we have found this box before and not visited
                    qu.push(boxKey); // Add to queue for further processing
                    visited.insert(boxKey); // Mark as visited
                    totalCandies += candies[boxKey]; // Collect candies from this box
                }
            }
        }
    }
    */

    return totalCandies;
}

int main() {
    vector<int> status = {1, 0, 1, 0};
    vector<int> candies = {7, 5, 4, 100};
    vector<vector<int>> keys = {{}, {}, {1}, {}};
    vector<vector<int>> containedBoxes = {{1, 2}, {3}, {}, {}};
    vector<int> initialBoxes = {0};

    int result = maxCandies(status, candies, keys, containedBoxes, initialBoxes);
    cout << "Maximum candies you can get: " << result << endl; // Output: 16

    return 0;
}