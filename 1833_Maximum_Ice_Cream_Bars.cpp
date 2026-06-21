/*
Maximum Ice Cream Bars - [Leetcode - 1833(Medium)]
------------------------------------------------------

It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 

Note: The boy can buy the ice cream bars in any order.

Return the maximum number of ice cream bars the boy can buy with coins coins.

You must solve the problem by counting sort.

Example 1:

Input: costs = [1,3,2,4,1], coins = 7
Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.

Example 2:

Input: costs = [10,6,8,7,7,8], coins = 5
Output: 0
Explanation: The boy cannot afford any of the ice cream bars.

Example 3:

Input: costs = [1,6,3,1,2,5], coins = 20
Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
 

Constraints:

costs.length == n
1 <= n <= 105
1 <= costs[i] <= 10^5
1 <= coins <= 10^8
*/

#include <iostream>
#include <vector>
using namespace std;

int maxIceCream(vector<int>& costs, int coins) {
    vector<int> count(100001, 0); // Create a counting array for costs up to 100000
    for (int cost : costs) {
        count[cost]++; // Count the occurrences of each cost
    }

    int totalBars = 0; // Initialize the total number of ice cream bars bought
    for (int price = 1; price <= 100000; price++) {
        if (count[price] > 0) { // If there are ice cream bars at this price
            int maxBarsAtPrice = min(count[price], coins / price); // Calculate how many bars can be bought at this price
            totalBars += maxBarsAtPrice; // Add to the total number of bars bought
            coins -= maxBarsAtPrice * price; // Deduct the spent coins
        }
        if (coins <= 0) break; // If no coins left, break the loop
    }

    return totalBars; // Return the total number of ice cream bars bought        
}

int main() {
    vector<int> costs = {1, 3, 2, 4, 1};
    int coins = 7;
    cout << maxIceCream(costs, coins) << endl; // Output: 4
    return 0;
}