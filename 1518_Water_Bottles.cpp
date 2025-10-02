/*
Water Bottles - [Leetcode - 1518(Easy)]
----------------------------------------
There are numBottles water bottles that are initially full of water. You can exchange numExchange empty water bottles from the market with one full water bottle.

The operation of drinking a full water bottle turns it into an empty bottle.

Given the two integers numBottles and numExchange, return the maximum number of water bottles you can drink.

Example 1:

Input: numBottles = 9, numExchange = 3
Output: 13
Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
Number of water bottles you can drink: 9 + 3 + 1 = 13.

Example 2:

Input: numBottles = 15, numExchange = 4
Output: 19
Explanation: You can exchange 4 empty bottles to get 1 full water bottle. 
Number of water bottles you can drink: 15 + 3 + 1 = 19.
 
Constraints:

1 <= numBottles <= 100
2 <= numExchange <= 100

*/

/*
============ Similar Problems Leetcode[1518] and Leetcode[3100] ============
Key differences: 1518 vs 3100

• Exchange cost:
  => 1518: Constant (fixed numExchange throughout).
  => 3100: Increases by 1 after each exchange.

• Exchange frequency:
  => 1518: You can effectively exchange as many times as empties allow at the same cost.
  => 3100: Only one exchange per cost level; cost rises, so total extra bottles is smaller.

• Edge case:
  => 1518 disallows numExchange = 1 (min is 2), avoiding infinite loop.
  => 3100 allows numExchange = 1 but prevents infinity because the cost bumps to 2 after the first exchange.

• Solution style:
  => 1518: Has a clean O(1) formula: numBottles + (numBottles − 1) / (numExchange − 1).
  => 3100: No simple closed form due to increasing cost; use greedy simulation.

*/

#include <iostream>
using namespace std;

// Approach - 1: Simulation
// Time Complexity: O(logn)
// Space Complexity: O(1)
int numWaterBottles(int numBottles, int numExchange) {
    int totalDrunk = numBottles;
    int emptyBottles = numBottles;

    while(emptyBottles >= numExchange){
        int newBottles = emptyBottles / numExchange;
        totalDrunk += newBottles;
        emptyBottles = emptyBottles % numExchange + newBottles;
    }

    return totalDrunk;
}

// Approach - 2: Mathematical Approach
// Time Complexity: O(1)
// Space Complexity: O(1)
int numWaterBottles(int numBottles, int numExchange) {
    return numBottles + (numBottles - 1) / (numExchange - 1);
}

// Approach - 3: Recursive Approach
// Time Complexity: O(logn)
// Space Complexity: O(logn) [Recursive Stack Space]
int helper(int emptyBottles, int numExchange) {
    if (emptyBottles < numExchange) {
        return 0;
    }
    int newBottles = emptyBottles / numExchange;
    return newBottles + helper(emptyBottles % numExchange + newBottles, numExchange);
}

int numWaterBottles(int numBottles, int numExchange) {
    return numBottles + helper(numBottles, numExchange);
}

int main() {
    int numBottles = 9, numExchange = 3;
    cout << numWaterBottles(numBottles, numExchange) << endl; // Output: 13
    return 0;
}