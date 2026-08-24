/*
Stone Game VIII - [Leetcode - 1872(HARD)]
------------------------------------------------
Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row. On each player's turn, while the number of stones is more than one, they will do the following:

Choose an integer x > 1, and remove the leftmost x stones from the row.
Add the sum of the removed stones' values to the player's score.
Place a new stone, whose value is equal to that sum, on the left side of the row.
The game stops when only one stone is left in the row.

The score difference between Alice and Bob is (Alice's score - Bob's score). Alice's goal is to maximize the score difference, and Bob's goal is the minimize the score difference.

Given an integer array stones of length n where stones[i] represents the value of the ith stone from the left, return the score difference between Alice and Bob if they both play optimally.
 

Example 1:

Input: stones = [-1,2,-3,4,-5]
Output: 5
Explanation:
- Alice removes the first 4 stones, adds (-1) + 2 + (-3) + 4 = 2 to her score, and places a stone of
  value 2 on the left. stones = [2,-5].
- Bob removes the first 2 stones, adds 2 + (-5) = -3 to his score, and places a stone of value -3 on
  the left. stones = [-3].
The difference between their scores is 2 - (-3) = 5.

Example 2:

Input: stones = [7,-6,5,10,5,-2,-6]
Output: 13
Explanation:
- Alice removes all stones, adds 7 + (-6) + 5 + 10 + 5 + (-2) + (-6) = 13 to her score, and places a
  stone of value 13 on the left. stones = [13].
The difference between their scores is 13 - 0 = 13.

Example 3:

Input: stones = [-10,-12]
Output: -22
Explanation:
- Alice can only make one move, which is to remove both stones. She adds (-10) + (-12) = -22 to her
  score and places a stone of value -22 on the left. stones = [-22].
The difference between their scores is (-22) - 0 = -22. 

Constraints:

n == stones.length
2 <= n <= 10^5
-104 <= stones[i] <= 10^4
*/

#include <iostream>
#include <vector>
using namespace std;

int helper(int i, vector<int>& prefixSum, vector<int>& dp) {
    int n = prefixSum.size();
    
    if(i == n-1){
        return prefixSum[n-1];
    }

    if(dp[i] != -1) {
        return dp[i];
    }

    int take = prefixSum[i] - helper(i + 1, prefixSum, dp);
    int skip = helper(i + 1, prefixSum, dp);

    return dp[i] = max(take, skip);
}

int stoneGameVIII(vector<int>& stones) {
    int n = stones.size();

    vector<int> dp(n, -1);
    
    vector<int> prefixSum(n);
    prefixSum[0] = stones[0];

    for (int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + stones[i];
    }

    return helper(1, prefixSum, dp); // Alice starts first, so we start from index 1
}

// Bottom-Up DP approach
int stoneGameVIII(vector<int>& stones) {
    int n = stones.size();

    vector<int> prefixSum(n, 0);
    prefixSum[0] = stones[0];

    for (int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + stones[i];
    }

    vector<int> dp(n, 0);
    // Base case: if(i == n-1), return prefixSum[n-1];
    dp[n - 1] = prefixSum[n - 1];

    for (int i = n - 2; i >= 1; i--) {
        int take = prefixSum[i] - dp[i + 1];
        int skip = dp[i + 1];

        dp[i] = max(take, skip);
    }

    return dp[1]; // Alice starts first, so we return the result from index 1
}

int main() {
    vector<int> stones1 = {-1, 2, -3, 4, -5};
    cout << "Output: " << stoneGameVIII(stones1) << endl; // Output: 5

    vector<int> stones2 = {7, -6, 5, 10, 5, -2, -6};
    cout << "Output: " << stoneGameVIII(stones2) << endl; // Output: 13

    vector<int> stones3 = {-10, -12};
    cout << "Output: " << stoneGameVIII(stones3) << endl; // Output: -22

    return 0;
}