/*
Count Square Sum Triples - [Leetcode - 1925(Easy)]
-----------------------------------------------------
A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.

Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.

Example 1:

Input: n = 5
Output: 2
Explanation: The square triples are (3,4,5) and (4,3,5).

Example 2:

Input: n = 10
Output: 4
Explanation: The square triples are (3,4,5), (4,3,5), (6,8,10), and (8,6,10).

Constraints:

1 <= n <= 250
*/

#include <iostream>
#include <cmath>
using namespace std;

// Approach  (Brute Force - Check for all combinations of a and b, if c is perfect square and within range)
int countTriples(int n) {
    int count = 0;

    for(int a = 1; a <= n; a++){
        for(int b = 1; b <= n; b++){
            for(int c = 1; c <= n; c++){
                if((a * a + b * b) == (c * c)){
                    count++;
                }
            }
        }
    }
    return count;
}

// Better Approach (Using square root to find c)
int countTriples(int n) {
    int count = 0;

    for(int a = 1; a <= n; a++){
        for(int b = a + 1; b <= n; b++){
            int cSquare = (a * a) + (b * b);
            int c = sqrt(cSquare);
            if(c * c == cSquare && c <= n){
                count += 2; // (a,b,c) and (b,a,c)
            }
        }
    }
    return count;
}

int main() {
    int n = 5;

    int result = countTriples(n);
    cout << "Number of square sum triples: " << result << endl;

    return 0;
}