/*
Pyramid Transition Matrix - [Leetcode - 756(Medium)]
------------------------------------------------------
You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row of blocks contains one less block than the row beneath it and is centered on top.

To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks respectively, and the third character is the top block.

For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right) block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.
You start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.

Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular pattern in the pyramid is in allowed, or false otherwise.

Example 1:

Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
Output: true
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 3), we can build "CE" on level 2 and then build "A" on level 1.
There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.

Example 2:

Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
Output: false
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 4), there are multiple ways to build level 3, but trying all the possibilites, you will get always stuck before building level 1.
 

Constraints:

2 <= bottom.length <= 6
0 <= allowed.length <= 216
allowed[i].length == 3
The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
All the values of allowed are unique.
*/

// BACKTRACING BASED PROBLEM
// Why use ? => Because we need to explore all the possible ways to build the pyramid from bottom to top

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

bool helper(string &curr, unordered_map<string, vector<char>> &map, int idx, string above, unordered_map<string, bool> &dp) {
    // Base Case: If we have reached the top of the pyramid
    if(curr.length() == 1) return true; // pyramid is built successfully

    string key = curr + "|" + to_string(idx) + "|" + above;

    if(dp.count(key)) return dp[key]; // already computed this state

    if(idx == curr.length() - 1){
        // time to move to the next level i.e. above row and it becomes the current row now
        return dp[key] = helper(above, map, 0, "", dp);
    }

    string pair = curr.substr(idx, 2); // get the current pair of blocks
    if(map.find(pair) == map.end()) return dp[key] = false; // no possible block can be placed on top of this pair i.e. this pair is not present in the allowed patterns

    // try all the possible blocks that can be placed on top of this pair
    // BACKTRACKING - DO, EXPLORE, UNDO
    for(auto &ch : map[pair]){
        // place this block on top of the pair
        above.push_back(ch); // DO
        
        // place the block on top of this pair and move to the next pair
        if(helper(curr, map, idx + 1, above, dp)) return dp[key] = true; // if we can build the pyramid successfully return true // EXPLORE
        
        // If we are here means we couldn't build the pyramid successfully with this choice
        above.pop_back(); // UNDO => backtracking
    }

    return dp[key] = false; // couldn't build the pyramid successfully
}

bool pyramidTransition(string bottom, vector<string>& allowed) {
    unordered_map<string, vector<char>> map; // to store all the possible top blocks for each pair of bottom blocks : {(AB) : [C, D, E]}

    unordered_map<string, bool> dp; // memoization map to store already computed states
    
    for(auto &pattern : allowed){
        map[pattern.substr(0, 2)].push_back(pattern[2]); // pattern.substr(0, 2) => first two characters of the pattern and pattern[2] => third character of the pattern that is the top block push into the vector
    }
    
    return helper(bottom, map, 0, "", dp); // start from index 0 and empty next level string
}

int main() {
    string bottom = "BCD";
    vector<string> allowed = {"BCC", "CDE", "CEA", "FFF"};

    if (pyramidTransition(bottom, allowed)) {
        cout << "Pyramid can be built successfully." << endl;
    } else {
        cout << "Pyramid cannot be built." << endl;
    }

    return 0;
}