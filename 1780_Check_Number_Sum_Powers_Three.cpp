/*
Check if Number is a Sum of Powers of Three - [ Leetcode - Medium (1780)]
=========================================================================
Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.

An integer y is a power of three if there exists an integer x such that y == 3x.


Example 1:

Input: n = 12
Output: true
Explanation: 12 = 3^1 + 3^2
Example 2:

Input: n = 91
Output: true
Explanation: 91 = 3^0 + 3^2 + 3^4

Example 3:

Input: n = 21
Output: false
 

Constraints:

1 <= n <= 107
*/ 

#include <iostream>
#include <cmath>
using namespace std;

bool checkPowersOfThree(int n){
    while(n > 0){
        // i.e if remainder is 0 & 1 -> true.
        // if remainder is 2 -> return false.
        if(n % 3 == 2) return false;
        n /= 3;
    }
    return true;
}

int main(){
    
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    
    cout<<boolalpha<<checkPowersOfThree(n);
    
    return 0;
}