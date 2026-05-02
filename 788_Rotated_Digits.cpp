/*
Rotated Digits - [Leetcode - 788(Medium)]
-------------------------------------------
An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

0, 1, and 8 rotate to themselves,
2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
6 and 9 rotate to each other, and
the rest of the numbers do not rotate to any other number and become invalid.
Given an integer n, return the number of good integers in the range [1, n].

Example 1:

Input: n = 10
Output: 4
Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.

Example 2:

Input: n = 1
Output: 0

Example 3:

Input: n = 2
Output: 1

Constraints:

1 <= n <= 10^4
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach - 1: Using String
int rotatedDigits(int n) {
    int count = 0;

    for(int i=1; i<=n; i++){
        string num = to_string(i);
        bool isValid = true;
        bool isDifferent = false;

        for(char c : num){
            if(c == '3' || c == '4' || c == '7'){
                isValid = false;
                break;
            }
            if(c == '2' || c == '5' || c == '6' || c == '9'){
                isDifferent = true;
            }
        }

        if(isValid && isDifferent){
            count++;
        }
    }
    return count;
}

// Approach - 2: Using Integer
bool isGood(int num){
    bool changed = false;

    while(num > 0){
        int digit = num % 10;
        if(digit == 3 || digit == 4 || digit == 7){
            return false;
        }
        if(digit == 2 || digit == 5 || digit == 6 || digit == 9){
            changed = true;
        }
        num /= 10;
    }
    return changed;
}

int rotatedDigits(int n) {
    int count = 0;

    for(int i=1; i<=n; i++){
        if(isGood(i)){
            count++;
        }
    }
    return count;
}

// Approach - 3: Using Recursion + Memoization
int helper(int num, vector<int> &dp) {
    if(dp[num] != -1) return dp[num];
    if(num == 0) return dp[num] = 0;
    
    int remain = helper(num/10, dp);
    if(remain == 2) return dp[num] = 2;
    int digit_check;
    
    int d = num%10;
    
    if (d == 0 || d == 1 || d == 8) digit_check = 0;       // same
    else if (d == 2 || d == 5 || d == 6 || d == 9) digit_check = 1;       // good
    else return dp[num] = 2;     // invalid
    
    if(remain == 0 && digit_check == 0) {
        return dp[num] = 0;
    }
    
    return dp[num] = 1;
}

// Approach - 4: Using Bottom-Up DP
int rotatedDigits(int n) {
    int count = 0;

    vector<int> dp(n+1, -1);

    //0 : same
    //1 : Good
    //2 : invalid
    for(int i = 1; i <= n; i++) {
        int remain = dp[i/10];
        if(remain == 2) {
            dp[i] = 2;
            continue;
        }
        
        int digit_check;
        int d = i%10;
        
        if (d == 0 || d == 1 || d == 8) digit_check = 0;       // same
        else if (d == 2 || d == 5 || d == 6 || d == 9) digit_check = 1;       // good
        else {
            dp[i] = 2;     // invalid
            continue;
        }
        
        if(remain == 0 && digit_check == 0) {
            dp[i] = 0;
        } else {
            dp[i] = 1;
            count++;
        }
    }

    return count;
}

int rotatedDigits(int n) {
    int count = 0;

    vector<int> dp(n+1, -1);

    //0 : same
    //1 : Good
    //2 : invalid
    for(int i = 1; i <= n; i++) {
        if(helper(i, dp) == 1) {
            count++;
        }
    }

    return count;
}