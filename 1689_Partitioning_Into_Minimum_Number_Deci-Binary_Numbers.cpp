/*
Partitioning Into Minimum Number Of Deci-Binary Numbers - [Leetcode - 1689(Medium)]
---------------------------------------------------------------------------------------
A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.

Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.

Example 1:

Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32

Example 2:

Input: n = "82734"
Output: 8
Example 3:

Input: n = "27346209830709182346"
Output: 9

Constraints:

1 <= n.length <= 10^5
n consists of only digits.
n does not contain any leading zeros and represents a positive integer.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Approach - 1: Brute Force
int minPartitions(string n) {
    int count = 0;

    while(true){
        bool changed = false; // flag to check if any digit was changed in this iteration
        for(auto & ch : n){
            if(ch != '0'){
                ch--; // subtract 1 from the current digit
                changed = true;
            }
        }
        if(!changed) break; // if no digit was changed, we are done
        count++; // increment the count of deci-binary numbers
    }
    return count;
}

// Approach - 2: Trick or CPP inbuilt method
int minPartitions(string n) {
    char maximumChar = *max_element(n.begin(), n.end()); // find the maximum character in the string
    return maximumChar - '0'; // convert the character to an integer and return it
}

int main(){
    string n = "27346209830709182346";
    cout << minPartitions(n) << endl;
    return 0;
}