/*
Number of Steps to Reduce a Number in Binary Representation to One - [Leetcode - 1404(Medium)]
------------------------------------------------------------------------------------------------
Given the binary representation of an integer as a string s, return the number of steps to reduce it to 1 under the following rules:

If the current number is even, you have to divide it by 2.

If the current number is odd, you have to add 1 to it.

It is guaranteed that you can always reach one for all test cases.

Example 1:

Input: s = "1101"
Output: 6
Explanation: "1101" corressponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14.
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.
Step 5) 4 is even, divide by 2 and obtain 2.
Step 6) 2 is even, divide by 2 and obtain 1.

Example 2:

Input: s = "10"
Output: 1
Explanation: "10" corresponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.
Example 3:

Input: s = "1"
Output: 0

Constraints:

1 <= s.length <= 500
s consists of characters '0' or '1'
s[0] == '1'
*/

#include <iostream>
#include <string>
using namespace std;

void addOne(string& s) {
    int i = s.length() - 1;
    
    while(i >= 0 && s[i] != '0'){
        s[i] = '0';
        i--;
    }

    if (i < 0){
        s = '1' + s;
    } else{
        s[i] = '1';
    }
}

int numSteps(string s) {
    int operations = 0;
    
    while (s.length() > 1){
        int n = s.length();
        
        if (s[n - 1] == '0'){
            s.pop_back();
        } else{
            addOne(s);
        }
    }
    return operations;
}

// Optimal Approach 
int numSteps(string s) {
    int n = s.length();

    int operation = 0;
    int carry = 0;

    for(int i=n-1; i>=1; i--){
        if((s[i] - '0' + carry) % 2 == 1){
            operation += 2; // odd number: add 1 and then divide by 2
            carry = 1; // after adding 1, we will have a carry for the
        } else {
            operation += 1; // even number: just divide by 2
        }
    }
    return operation + carry; // add carry for the last bit if needed
}


int main() {
    string s1 = "1101";
    cout << numSteps(s1) << endl; // Output: 6

    string s2 = "10";
    cout << numSteps(s2) << endl; // Output: 1

    string s3 = "1";
    cout << numSteps(s3) << endl; // Output: 0

    return 0;
}