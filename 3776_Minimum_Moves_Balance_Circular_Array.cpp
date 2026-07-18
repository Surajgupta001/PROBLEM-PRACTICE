/*
Minimum Moves to Balance Circular Array - [Leetcode - 3776(Medium)]
----------------------------------------------------------------------
You are given a circular array balance of length n, where balance[i] is the net balance of person i.

In one move, a person can transfer exactly 1 unit of balance to either their left or right neighbor.

Return the minimum number of moves required so that every person has a non-negative balance. If it is impossible, return -1.

Note: You are guaranteed that at most 1 index has a negative balance initially.

Example 1:

Input: balance = [5,1,-4]

Output: 4

Explanation:

One optimal sequence of moves is:

Move 1 unit from i = 1 to i = 2, resulting in balance = [5, 0, -3]
Move 1 unit from i = 0 to i = 2, resulting in balance = [4, 0, -2]
Move 1 unit from i = 0 to i = 2, resulting in balance = [3, 0, -1]
Move 1 unit from i = 0 to i = 2, resulting in balance = [2, 0, 0]
Thus, the minimum number of moves required is 4.

Example 2:

Input: balance = [1,2,-5,2]

Output: 6

Explanation:

One optimal sequence of moves is:

Move 1 unit from i = 1 to i = 2, resulting in balance = [1, 1, -4, 2]
Move 1 unit from i = 1 to i = 2, resulting in balance = [1, 0, -3, 2]
Move 1 unit from i = 3 to i = 2, resulting in balance = [1, 0, -2, 1]
Move 1 unit from i = 3 to i = 2, resulting in balance = [1, 0, -1, 0]
Move 1 unit from i = 0 to i = 1, resulting in balance = [0, 1, -1, 0]
Move 1 unit from i = 1 to i = 2, resulting in balance = [0, 0, 0, 0]
Thus, the minimum number of moves required is 6.​​​

Example 3:

Input: balance = [-3,2]

Output: -1

Explanation:

​​​​​​​It is impossible to make all balances non-negative for balance = [-3, 2], so the answer is -1.

Constraints:

1 <= n == balance.length <= 10^5
-10^9 <= balance[i] <= 10^9
There is at most one negative value in balance initially.
*/

#include <iostream>
#include <vector>
using namespace std;

long long minMoves(vector<int>& balance) {
    int n = balance.size();
    
    int culpritIndex = -1;
    long long sum = 0;

    for(int i=0; i<n; i++){
        sum += balance[i];
        if(balance[i] < 0){
            if(culpritIndex != -1) return -1; // More than one negative balance
            culpritIndex = i;
        }
    }

    if(culpritIndex == -1) return 0; // No negative balance, no moves needed

    if(sum < 0) return -1; // Total balance is negative, impossible to balance

    long long moves = 0;
    int distance = 1;

    while(balance[culpritIndex] < 0){
        int left = (culpritIndex + distance) % n;
        int right = (culpritIndex - distance + n) % n;

        long long available = balance[left] + balance[right];
        if(left == right){
            available -= balance[left]; // Avoid double counting if left and right are the same
        }
        
        long long needed = -balance[culpritIndex];
        long long taken = min(needed, available);

        moves += taken*distance;
        balance[culpritIndex] += taken;

        distance++;
    }

    return moves;
}

int main() {
    vector<int> balance1 = {5, 1, -4};
    vector<int> balance2 = {1, 2, -5, 2};
    vector<int> balance3 = {-3, 2};

    cout << "Minimum moves for balance1: " << minMoves(balance1) << endl; // Output: 4
    cout << "Minimum moves for balance2: " << minMoves(balance2) << endl; // Output: 6
    cout << "Minimum moves for balance3: " << minMoves(balance3) << endl; // Output: -1

    return 0;
}