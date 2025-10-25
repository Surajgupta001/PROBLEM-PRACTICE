/*
Next Greater Numerically Balanced Number - [Leetcode - 2048(Medium)]
---------------------------------------------------------------------
An integer x is numerically balanced if for every digit d in the number x, there are exactly d occurrences of that digit in x.

Given an integer n, return the smallest numerically balanced number strictly greater than n.

 

Example 1:

Input: n = 1
Output: 22
Explanation: 
22 is numerically balanced since:
- The digit 2 occurs 2 times. 
It is also the smallest numerically balanced number strictly greater than 1.
Example 2:

Input: n = 1000
Output: 1333
Explanation: 
1333 is numerically balanced since:
- The digit 1 occurs 1 time.
- The digit 3 occurs 3 times. 
It is also the smallest numerically balanced number strictly greater than 1000.
Note that 1022 cannot be the answer because 0 appeared more than 0 times.
Example 3:

Input: n = 3000
Output: 3133
Explanation: 
3133 is numerically balanced since:
- The digit 1 occurs 1 time.
- The digit 3 occurs 3 times.
It is also the smallest numerically balanced number strictly greater than 3000.
 

Constraints:

0 <= n <= 10^6
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Approach - 1 : Simulation
bool balanced(int num) {
    vector<int> freq(10);
    while(num > 0){
        int digit = num % 10;
        freq[digit]++;
        num /= 10;
    }

    for(int d = 0; d < 10; d++){
        if(freq[d] != 0 && freq[d] != d){
            return false;
        }
    }
    return true;
}

int nextBeautifulNumber(int n) {
    for(int num = n+1; num <= 1224444; num++){
        if(balanced(num)){
            return num;
        }
    }
    return -1;
}

// Approach - 2 : Upper Bound (Precomputation) -> not preferred as it requires extra space for storing precomputed values.

// Approach - 3 : Backtracking (Generating all numerically balanced numbers up to 10^7)
vector<int> digitCount = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int backtracking(int n, int currentNum, int count) {
    if(count == 0){
        for(int digit=1; digit<=9; digit++){
            if(digitCount[digit] != 0 && digitCount[digit] != digit){
                return 0;
            }
        }
        return currentNum > n ? currentNum : 0;
    }

    int result = 0;
    
    for(int digit = 1; digit <= 9; digit++){
        if(digitCount[digit] > 0 && digitCount[digit]  <= count){
            digitCount[digit] --;
            result = backtracking(n, currentNum * 10 + digit, count - 1);
            digitCount[digit] ++;
        }
        if(result != 0){
            break;
        }
    }
    return result;
}
int nextBeautifulNumber(int n) {
    int numDigits = to_string(n).length();
    int result = backtracking(n, 0, numDigits);
    if(result == 0){
        result = backtracking(n, 0, numDigits + 1);
    }
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    int result = nextBeautifulNumber(n);
    cout << "The next greater numerically balanced number is: " << result << endl;
    return 0;
}