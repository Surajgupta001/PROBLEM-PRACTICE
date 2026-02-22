/*
Binary Gap - [Leetcode - 868(Easy)]
------------------------------------
Given a positive integer n, find and return the longest distance between any two adjacent 1's in the binary representation of n. If there are no two adjacent 1's, return 0.

Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance between two 1's is the absolute difference between their bit positions. For example, the two 1's in "1001" have a distance of 3.

Example 1:

Input: n = 22
Output: 2
Explanation: 22 in binary is "10110".
The first adjacent pair of 1's is "10110" with a distance of 2.
The second adjacent pair of 1's is "10110" with a distance of 1.
The answer is the largest of these two distances, which is 2.
Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.

Example 2:

Input: n = 8
Output: 0
Explanation: 8 in binary is "1000".
There are not any adjacent pairs of 1's in the binary representation of 8, so we return 0.

Example 3:

Input: n = 5
Output: 2
Explanation: 5 in binary is "101".


Constraints:

1 <= n <= 109
*/

#include <iostream>
#include <vector>
using namespace std;

//Approach-1 (Simple bit checking)
//T.C : ~O(32) i.e. O(1)
//S.C : O(1)
int binaryGap(int n) {
    int prev = -1;
    int curr = 0;

    int result = 0;

    while(n > 0){
        if((n&1) > 0){
            if(prev != -1){
                result = max(result, curr - prev);
            }
            prev = curr;
        }
        curr++;
        n >>= 1;
    }
    return result;
}


//Approach-2 (Simple bit checking)
//T.C : ~O(32) i.e. O(1)
//S.C : O(1)
// int binaryGap(int n) {
//     int prev = -1;
//     int result = 0;

//     for(int curr = 0; curr < 32; curr++){
//         if(((n >> curr) & 1) > 0){
//             result = (prev != -1) ? max(result, curr-prev) : result;
//             prev = curr;
//         }
//     }
//     return result;
// }

int main() {
    int n = 22;
    cout << binaryGap(n) << endl; // Output: 2

    n = 8;
    cout << binaryGap(n) << endl; // Output: 0

    n = 5;
    cout << binaryGap(n) << endl; // Output: 2

    return 0;
}