/*
Total Waviness of Numbers in Range I - [Leetcode - 3751(Medium)]
------------------------------------------------------------------------
You are given two integers num1 and num2 representing an inclusive range [num1, num2].

The waviness of a number is defined as the total count of its peaks and valleys:

A digit is a peak if it is strictly greater than both of its immediate neighbors.
A digit is a valley if it is strictly less than both of its immediate neighbors.
The first and last digits of a number cannot be peaks or valleys.
Any number with fewer than 3 digits has a waviness of 0.
Return the total sum of waviness for all numbers in the range [num1, num2].
 

Example 1:

Input: num1 = 120, num2 = 130

Output: 3

Explanation:

In the range [120, 130]:
120: middle digit 2 is a peak, waviness = 1.
121: middle digit 2 is a peak, waviness = 1.
130: middle digit 3 is a peak, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 2:

Input: num1 = 198, num2 = 202

Output: 3

Explanation:

In the range [198, 202]:
198: middle digit 9 is a peak, waviness = 1.
201: middle digit 0 is a valley, waviness = 1.
202: middle digit 0 is a valley, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 3:

Input: num1 = 4848, num2 = 4848

Output: 2

Explanation:

Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

Constraints:

1 <= num1 <= num2 <= 10^5
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int totalWaviness(int num1, int num2) {
    int totalWaviness = 0;

    for(int num = num1; num <= num2; num++){
        string strNum = to_string(num);
        int len = strNum.length();

        if(len < 3) continue; // Waviness is 0 for numbers with less than 3 digits
        
        for(int i = 1; i < len - 1; i++){
            if((strNum[i] > strNum[i-1] && strNum[i] > strNum[i+1]) || 
               (strNum[i] < strNum[i-1] && strNum[i] < strNum[i+1])){
                totalWaviness++;
            }
        }
    }
    return totalWaviness;
}

int main() {
    int num1 = 120, num2 = 130;
    cout << "Total Waviness: " << totalWaviness(num1, num2) << endl; // Output: 3

    num1 = 198, num2 = 202;
    cout << "Total Waviness: " << totalWaviness(num1, num2) << endl; // Output: 3

    num1 = 4848, num2 = 4848;
    cout << "Total Waviness: " << totalWaviness(num1, num2) << endl; // Output: 2

    return 0;
}