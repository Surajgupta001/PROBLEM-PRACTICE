/*
Maximum 69 Number - [Leetcode - 1323(Easy)]
You are given a positive integer num consisting only of digits 6 and 9.

Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).

Example 1:

Input: num = 9669
Output: 9969
Explanation: 
Changing the first digit results in 6669.
Changing the second digit results in 9969.
Changing the third digit results in 9699.
Changing the fourth digit results in 9666.
The maximum number is 9969.

Example 2:

Input: num = 9996
Output: 9999
Explanation: Changing the last digit 6 to 9 results in the maximum number.

Example 3:

Input: num = 9999,
Output: 9999
Explanation: It is better not to apply any change.
*/

#include <iostream>
#include <cmath>
using namespace std;

int maximum69Number(int num) {
    int i = 0; // Position of the last digit
    int j = -1; // Position of the last '6'

    // Store the original number
    int originalNum = num;

    while(num){
        if(num % 10 == 6){
            j = i; // Store the position of the last '6'
        }
        i++;
        num /= 10;
    }

    // No '6' found, return original number
    if (j == -1) return originalNum;

    // Change the last '6' to '9'
    return originalNum + (3 * pow(10, j)); // 9 - 6 = 3
}

int main(){

    int n;
    cout<<"Enter a number: ";
    cin>>n;

    int ans = maximum69Number(n);
    cout << "Maximum number after changing at most one digit: " << ans << endl;

    return 0;
}