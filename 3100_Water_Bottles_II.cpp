/*
Water Bottles II - [Leetcode - 3100(Medium)]
----------------------------------------------
You are given two integers numBottles and numExchange.

numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:

Drink any number of full water bottles turning them into empty bottles.
Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
Note that you cannot exchange multiple batches of empty bottles for the same cost. For example, if numExchange == 3 and you have 6 empty bottles, you cannot exchange 6 empty bottles for 2 bottles.

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

#include <iostream>
using namespace std;

// Approach: Greedy Simulation
// Time Complexity: O(number of exchanges) ≈ O(answer)
// Space Complexity: O(1)
int maxBottlesDrunk(int numBottles, int numExchange) {
    int total = numBottles;      // drink all initial bottles
    int empty = numBottles;      // they become empty

    while (empty >= numExchange) {
        empty -= numExchange;    // spend empties for 1 full
        total += 1;              // drink it
        empty += 1;              // it becomes empty
        numExchange += 1;        // cost increases
    }
    return total;
}

int main() {
    // Test case 1
    int numBottles1 = 13, numExchange1 = 6;
    cout << "Example 1: numBottles = " << numBottles1 << ", numExchange = " << numExchange1 << endl;
    cout << "Output: " << maxBottlesDrunk(numBottles1, numExchange1) << endl; // Output: 15
    cout << endl;

    // Test case 2
    int numBottles2 = 10, numExchange2 = 3;
    cout << "Example 2: numBottles = " << numBottles2 << ", numExchange = " << numExchange2 << endl;
    cout << "Output: " << maxBottlesDrunk(numBottles2, numExchange2) << endl; // Output: 13
    cout << endl;

    return 0;
}
