/*
Count Odd Numbers in an Interval Range - [Leetcode - 1523(Easy)]
-----------------------------------------------------------------
Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).

Example 1:

Input: low = 3, high = 7
Output: 3
Explanation: The odd numbers between 3 and 7 are [3,5,7].

Example 2:

Input: low = 8, high = 10
Output: 1
Explanation: The odd numbers between 8 and 10 are [9].
 
Constraints:

0 <= low <= high <= 10^9
*/ 

#include <iostream>
using namespace std;

int countOdds(int low, int high) {    
    // if low is even, make it odd
    if(low % 2 == 0) {
        low++;
    }

    // if high is even, make it odd
    if(high % 2 == 0) {
        high--;
    }
    
    // number of odds = ((high - low) / 2) + 1
    return ((high - low) / 2) + 1;
}

int main() {
    int low = 3, high = 7;
    cout << "Count of odd numbers between " << low << " and " << high << " is: " << countOdds(low, high) << endl;

    low = 8, high = 10;
    cout << "Count of odd numbers between " << low << " and " << high << " is: " << countOdds(low, high) << endl;

    return 0;
}