/*
Minimum Operations to Equalize Binary String - [Leetcode - 3666(Hard)]
---------------------------------------------------------------------------
You are given a binary string s, and an integer k.

In one operation, you must choose exactly k different indices and flip each '0' to '1' and each '1' to '0'.

Return the minimum number of operations required to make all characters in the string equal to '1'. If it is not possible, return -1.

Example 1:

Input: s = "110", k = 1

Output: 1

Explanation:

There is one '0' in s.
Since k = 1, we can flip it directly in one operation.
Example 2:

Input: s = "0101", k = 3

Output: 2

Explanation:

One optimal set of operations choosing k = 3 indices in each operation is:

Operation 1: Flip indices [0, 1, 3]. s changes from "0101" to "1000".
Operation 2: Flip indices [1, 2, 3]. s changes from "1000" to "1111".
Thus, the minimum number of operations is 2.

Example 3:

Input: s = "101", k = 2

Output: -1

Explanation:

Since k = 2 and s has only one '0', it is impossible to flip exactly k indices to make all '1'. Hence, the answer is -1.

Constraints:

1 <= s.length <= 10^5
s[i] is either '0' or '1'.
1 <= k <= s.length
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

// Brute Force BFS Solution => TLE
int minOperations(string s, int k) {
    int n = s.length();
    
    int startZero = 0;
    for(auto &ch: s){
        if(ch == '0') startZero++; // Correctly count total '0's
    }

    if(startZero == 0) return 0; // If there are no '0's, 0 operations needed.

    vector<int> operations(n+1, -1); // operations[z] = min operations required to reach state in which we have z '0's left in the string.

    queue<int> qu;
    qu.push(startZero);
    operations[startZero] = 0;

    while(!qu.empty()){
        int z = qu.front();
        qu.pop();

        int minF = max(0, k - (n - z)); // Corrected minimum '0's we must flip
        int maxF = min(k, z); // Maximum number of '0's we can flip in one operation.

        for(int f = minF; f <= maxF; f++){
            int newZ = z + k - 2*f; // New number of '0's after flipping f '0's and (k-f) '1's.

            if(operations[newZ] == -1){ // If we haven't visited this state before.
                operations[newZ] = operations[z] + 1; // Update the number of operations required to reach this new state.
                
                if(newZ == 0) return operations[newZ]; // If we have reached the state where all characters are '1', return the number of operations.
                qu.push(newZ); // Add the new state to the queue for further exploration.
            }
        }
    }
    return -1; // If we exhaust the queue without reaching the state where all characters are '1', return -1.
}

// Optimized BFS Solution => Accepted
int minOperations(string s, int k) {
    int n = s.length();
    
    int startZero = 0;
    for(auto &ch: s){
        if(ch == '0') startZero++; // Correctly count total '0's
    }

    if(startZero == 0) return 0; // If there are no '0's, 0 operations needed.

    set<int> evenSet; // Set of states (number of '0's) that can be reached in an even number of operations.
    set<int> oddSet; // Set of states (number of '0's) that can be reached in an odd number of operations.

    // Precompute the states that can be reached in even and odd number of operations.
    for(int count = 0; count <= n; count++){
        if(count % 2 == 0) evenSet.insert(count); // States with even number of '0's can be reached in an even number of operations.
        else oddSet.insert(count); // States with odd number of '0's can be reached in an odd number of operations.
    }

    vector<int> operations(n+1, -1); // operations[z] = min operations required to reach state in which we have z '0's left in the string.

    queue<int> qu;
    qu.push(startZero);
    operations[startZero] = 0;

    if(startZero % 2 == 0) {
        evenSet.erase(startZero);
    } else {
        oddSet.erase(startZero);
    }

    while(!qu.empty()){
        int z = qu.front();
        qu.pop();

        int minF = max(0, k - (n - z)); // Corrected minimum '0's we must flip
        int maxF = min(k, z); // Maximum number of '0's we can flip in one operation.

        // Corrected calculation for true min and max ranges
        int min_new_z = z + k - 2 * maxF; 
        int max_new_z = z + k - 2 * minF; 

        set<int> &currSet = (min_new_z % 2 == 0) ? evenSet : oddSet; // Determine which set to use based on the parity of the new state.

        auto itr = currSet.lower_bound(min_new_z); // Find the first state in the current set that is greater than or equal to actual_min_new_z.
        while(itr != currSet.end() && *itr <= max_new_z){ // Iterate through the states in the current set that are within the range of new states.
            int newZ = *itr; // Get the new state (number of '0's).
            
            if(operations[newZ] == -1){ // If we haven't visited this state before.
                operations[newZ] = operations[z] + 1; // Update the number of operations required to reach this new state.
                
                if(newZ == 0) return operations[newZ]; // If we have reached the state where all characters are '1', return the number of operations.
                qu.push(newZ); // Add the new state to the queue for further exploration.
            }
            itr = currSet.erase(itr); // Remove the state from the set to avoid revisiting it in the future.
        }
    }
    return -1; // If we exhaust the queue without reaching the state where all characters are '1', return -1.
}

int main() {
    string s1 = "110";
    int k1 = 1;
    cout << minOperations(s1, k1) << endl; // Output: 1

    string s2 = "0101";
    int k2 = 3;
    cout << minOperations(s2, k2) << endl; // Output: 2

    string s3 = "101";
    int k3 = 2;
    cout << minOperations(s3, k3) << endl; // Output: -1

    return 0;
}