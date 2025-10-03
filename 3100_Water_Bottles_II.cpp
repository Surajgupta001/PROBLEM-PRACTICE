/*
Water Bottles II - [Leetcode - 3100(Medium)]
---------------------------------------------
You are given two integers numBottles and numExchange.

numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:

Drink any number of full water bottles turning them into empty bottles.
Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.

Return the maximum number of water bottles you can drink.

Example 1:

Input: numBottles = 13, numExchange = 6
Output: 15
Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.

Example 2:

Input: numBottles = 10, numExchange = 3
Output: 13
Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.

Constraints:

1 <= numBottles <= 100
1 <= numExchange <= 100
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
#include <cmath>
using namespace std;

// Approach - 1: Simulation
// Time Complexity: O(n)
// Space Complexity: O(1)
int maxBottlesDrunk(int numBottles, int numExchange){
  int totalDrunk = numBottles;
  int emptyBottles = numBottles;

  while(emptyBottles >= numExchange){
    // Only one exchange per cost level
    emptyBottles -= numExchange; // spend empties for 1 full bottle
    totalDrunk += 1;             // drink it
    emptyBottles += 1;           // becomes empty
    numExchange += 1;            // cost increases
  }

  return totalDrunk;
}

// Approach - 2: Mathematical Derivation (Not Implemented)
// Time Complexity:
// Space Complexity: O(1)
int maxBottlesDrunk(int numBottles, int numExchange){
  return numBottles + ((-2*numExchange + 3 + sqrt(4*numExchange*numExchange+8*numBottles - 12 * numExchange + 1))/2);
}

int main(){
  int numBottles = 13, numExchange = 6;
  cout << "Maximum bottles drunk: " << maxBottlesDrunk(numBottles, numExchange) << endl; // Output: 15

  numBottles = 10, numExchange = 3;
  cout << "Maximum bottles drunk: " << maxBottlesDrunk(numBottles, numExchange) << endl; // Output: 13

  return 0;
}