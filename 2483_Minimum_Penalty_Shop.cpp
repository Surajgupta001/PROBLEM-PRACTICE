/*
Minimum Penalty for a Shop - [Leetcode - 2483(Medium)]
---------------------------------------------------------
You are given the customer visit log of a shop represented by a 0-indexed string customers consisting only of characters 'N' and 'Y':

if the ith character is 'Y', it means that customers come at the ith hour
whereas 'N' indicates that no customers come at the ith hour.
If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:

For every hour when the shop is open and no customers come, the penalty increases by 1.
For every hour when the shop is closed and customers come, the penalty increases by 1.
Return the earliest hour at which the shop must be closed to incur a minimum penalty.

Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.

Example 1:

Input: customers = "YYNY"
Output: 2
Explanation: 
- Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
- Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
- Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
- Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
- Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.

Example 2:

Input: customers = "NNNNN"
Output: 0
Explanation: It is best to close the shop at the 0th hour as no customers arrive.
Example 3:

Input: customers = "YYYY"
Output: 4
Explanation: It is best to close the shop at the 4th hour as customers arrive at each hour.
 

Constraints:

1 <= customers.length <= 10^5
customers consists only of characters 'Y' and 'N'.

*/

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

// Approach 1 : Brute Force => TLE
int bestClosingTime(string customers) {
    int n = customers.length();
    
    int minPenalty = INT_MAX;
    int bestHour = 0;
    
    for(int i=0; i<=n; i++){
        int penalty = 0;

        // Calculate penalty for closing at hour i
        for(int j=0; j<n; j++){
            if(j < i && customers[j] == 'N'){
                penalty++; // Shop is open but no customers
            }
            else if(j >= i && customers[j] == 'Y'){
                penalty++; // Shop is closed but customers come
            }
            else {
                // No penalty
                continue;
            }
        }
        // Update minimum penalty and best hour
        if(penalty < minPenalty){
            minPenalty = penalty;
            bestHour = i;
        }
    }
    return bestHour;
}

// Approach 2 : Prefix Sum and suffix sum
// Time Complexity: O(n)
// Space Complexity: O(n)
int bestClosingTime(string customers) {
    int n = customers.length();
    
    // Prefix and suffix arrays
    vector<int> prefix_N(n+1, 0); // Count of 'N's from start to i-1 => Left side from ith index
    vector<int> suffix_Y(n+1, 0); // Count of 'Y's from i to end => Right side from ith index

    // Fill prefix_N
    for(int i=1; i<=n; i++){
        prefix_N[i] = prefix_N[i-1] + (customers[i-1] == 'N' ? 1 : 0);
    }

    // Fill suffix_Y
    for(int i=n-1; i>=0; i--){
        suffix_Y[i] = suffix_Y[i+1] + (customers[i] == 'Y' ? 1 : 0);
    }

    int minPenalty = INT_MAX;
    int bestHour = 0;

    for(int i=0; i<=n; i++){
        int penalty = prefix_N[i] + suffix_Y[i];
        
        // Update minimum penalty and best hour
        if(penalty < minPenalty){
            minPenalty = penalty;
            bestHour = i;
        }
    }
    return bestHour;
}

// Better Approach 3 : 
// Time Complexity: O(n)
// Space Complexity: O(1)
int bestClosingTime(string customers) {
    int n = customers.length();
    
    int penalty = 0; // This tracks the relative penalty (score)
    int minPenalty = 0;
    int bestHour = 0;

    for(int i=0; i<=n; i++){
        // Update penalty for closing at hour i
        if(i > 0){
            if(customers[i-1] == 'Y'){
                penalty--; // Shop open, customer came -> Good -> Penalty decreases
            } else {
                penalty++; // Shop open, no customer -> Bad -> Penalty increases
            }
        }

        // Update minimum penalty and best hour
        if(penalty < minPenalty){
            minPenalty = penalty;
            bestHour = i;
        }
    }
    return bestHour;
}

int main() {
    string customers = "YYNY";
    cout << "Best Closing Time: " << bestClosingTime(customers) << endl;
    return 0;
}
// filepath: c:\Programming\C++ programming\PROBLEM PRACTICE\2483_Minimum_Penalty_Shop.cpp