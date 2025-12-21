/*
Best Time to Buy and Sell Stock V - [Leetcode - 3573(Medium)]
---------------------------------------------------------------
You are given an integer array prices where prices[i] is the price of a stock in dollars on the ith day, and an integer k.

You are allowed to make at most k transactions, where each transaction can be either of the following:

Normal transaction: Buy on day i, then sell on a later day j where i < j. You profit prices[j] - prices[i].

Short selling transaction: Sell on day i, then buy back on a later day j where i < j. You profit prices[i] - prices[j].

Note that you must complete each transaction before starting another. Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.

Return the maximum total profit you can earn by making at most k transactions.

Example 1:

Input: prices = [1,7,9,8,2], k = 2

Output: 14

Explanation:

We can make $14 of profit through 2 transactions:
A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.
Example 2:

Input: prices = [12,16,19,19,8,1,19,13,9], k = 3

Output: 36

Explanation:

We can make $36 of profit through 3 transactions:
A normal transaction: buy the stock on day 0 for $12 then sell it on day 2 for $19.
A short selling transaction: sell the stock on day 3 for $19 then buy back on day 4 for $8.
A normal transaction: buy the stock on day 5 for $1 then sell it on day 6 for $19.

Constraints:

2 <= prices.length <= 10^3
1 <= prices[i] <= 10^9
1 <= k <= prices.length / 2

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// CASE : 0 -> You have not bought anything and you have not short-sold anything.
// CASE : 1 -> Normal transaction - you had bought, now you will sell normally
// CASE : 2 -> Short selling transaction - you had sold, now you will buy back

long long helper(int i, int k, int CASE, vector<int>& prices, vector<vector<vector<long long>>> &dp) {
    
    if(i == prices.size()) {
        if (CASE == 0)
            return 0;
        return INT_MIN; //an unfinished transaction is invalid.
    }
    
    if (dp[i][k][CASE] != INT_MIN) return dp[i][k][CASE]; // memoization
    
    long long take = INT_MIN;
    long long dontTake;
    
    // Do nothing today
    dontTake = helper(i + 1, k, CASE, prices, dp);
    
    // Take action
    if (k > 0) {
        if (CASE == 1) {
            // Sell today (complete normal transaction)
            take = prices[i] + helper(i + 1, k - 1, 0, prices, dp);
        }
        else if (CASE == 2) {
            // Buy back today (complete short transaction)
            take = -prices[i] + helper(i + 1, k - 1, 0, prices, dp);
        }
        else {
            // CASE == 0: start a transaction
            take = max(
                -prices[i] + helper(i + 1, k, 1, prices, dp), // buy (normal)
                prices[i] + helper(i + 1, k, 2, prices, dp)  // short sell
            );
        }
    }
    return dp[i][k][CASE] = max(take, dontTake);
}

long long maximumProfit(vector<int>& prices, int k) {
    int n = prices.size();
    
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(3, INT_MIN)));
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= k; j++){
            for (int l = 0; l < 3; l++){
                dp[i][j][l] = INT_MIN;
            }
        }
    }
    return helper(0, k, 0, prices, dp);
}

// Buttom-up DP approach
long long maximumProfit(vector<int>& prices, int K) {
    int n = prices.size();
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(K + 1, vector<long long>(3, 0)));
    
    // Base case: when i == n, profit is 0 for all k and CASE
    for(int k = 0; k <= K; k++){
        dp[n][k][0] = 0;
        dp[n][k][1] = 0;
        dp[n][k][2] = 0;
    }

    // Fill the dp table
    for(int i = n-1; i >= 0; i--){
        for(int k = 0; k <= K; k++){

            // Don't take any action
            dp[i][k][0] = dp[i+1][k][0];

            // Take Action
            // CASE 0: Not holding any stock
            if(k > 0){
                dp[i][k][0] = max(dp[i][k][0], max(-prices[i] + dp[i+1][k][1], // buy (normal)
                                                        prices[i] + dp[i+1][k][2])); // short sell
            }

            // CASE 1: Holding stock from a normal buy
            dp[i][k][1] = dp[i+1][k][1]; // do nothing
            if(k > 0){
                dp[i][k][1] = max(dp[i][k][1], prices[i] + dp[i+1][k-1][0]); // sell
            }

            // CASE 2: Holding stock from a short sell
            dp[i][k][2] = dp[i+1][k][2]; // do nothing
            if(k > 0){
                dp[i][k][2] = max(dp[i][k][2], -prices[i] + dp[i+1][k-1][0]); // buy back
            }
        }
    }

    // Start from day 0, with K transactions left, and not holding any stock
    return dp[0][K][0];
}

int main(){
    vector<int> prices = {1, 7, 9, 8, 2};
    int k = 2;
    cout << "Maximum Profit: " << maximumProfit(prices, k) << endl;
}