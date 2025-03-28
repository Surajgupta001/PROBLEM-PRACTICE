/*

COMLEMENT OF BASE 10 INTEGER - (LEETCODE-1009)

The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer n, return its complement.

Example 1:

Input: n = 5
Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

Example 2:

Input: n = 7
Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

Example 3:

Input: n = 10
Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.
*/

#include <iostream>
using namespace std;

int bitwiseComplement(int n){
    /*
    * Time : O(log n)
    * Space : O(1)
    */ 
    if(n == 0) return 1;
    int mask = 0;
    int temp = n;

    // Calculate the number of bits in n
    while(temp > 0){
        mask = (mask << 1) | 1;
        // temp >>= 1; way to writing 
        temp = temp >> 1;
    }

    // Flip all the bits in n
    return n ^ mask;
}

int main(){
    
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    
    cout<<"The complement of "<<n<<" is "<<bitwiseComplement(n)<<endl;
    
    return 0;
}