/*
1-bit and 2-bit Characters - [Leetcode - 717(Easy)]
----------------------------------------------------
We have two special characters:

=> The first character can be represented by one bit 0.
=> The second character can be represented by two bits (10 or 11).
=> Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.

Example 1:

Input: bits = [1,0,0]
Output: true
Explanation: The only way to decode it is two-bit character and one-bit character.
So the last character is one-bit character.

Example 2:

Input: bits = [1,1,1,0]
Output: false
Explanation: The only way to decode it is two-bit character and two-bit character.
So the last character is not one-bit character.

Constraints:

1 <= bits.length <= 1000
bits[i] is either 0 or 1.
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Points to observe:
// (i) Last digit is always 0
// (ii) Two bits always start with 10 or 11

// Approach - 1:
bool isOneBitCharacter(vector<int>& bits) {
    int n = bits.size();
    int i = 0;

    while(i < n - 1){
        i += (bits[i] == 1) ? 2 : 1; // If bits[i] is 1, it is a two-bit character, so move 2 steps ahead; else move 1 step ahead
    }
    return i == n - 1; // If we land on the last index, it means the last character is a one-bit character
}

// Approach - 2:
bool isOneBitCharacter(vector<int>& bits) {
    int n = bits.size();
    int count1 = 0;

    for(int i=n-2; i>=0 && bits[i] == 1; i--){
        count1++;
    }
    return count1 % 2 == 0 ? true : false; // If count of consecutive 1's before last 0 is even, last character is one-bit character
}

int main() {
    vector<int> bits1 = {1, 0, 0};
    vector<int> bits2 = {1, 1, 1, 0};

    cout << boolalpha; // To print boolean values as true/false
    cout << "Example 1: " << isOneBitCharacter(bits1) << endl; // Output: true
    cout << "Example 2: " << isOneBitCharacter(bits2) << endl; // Output: false

    return 0;
}