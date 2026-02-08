/*
Minimum Deletions to Make String Balanced - [Leetcode - 1653(Medium)]
----------------------------------------------------------------------
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").

Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.

Constraints:

1 <= s.length <= 10^5
s[i] is 'a' or 'b'​​.
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// NOTE : In String's Problem => To delete a character => We First thing stack comes in mind, but here we can solve this problem without using stack, we can use two pointer approach to solve this problem

// // Approach 1 : Using Stack
// int minimumDeletions(string s) {
//     int n = s.size();

//     int count = 0;

//     stack<char> st;

//     for(int i=0; i<n; i++){
//         if(!st.empty() && s[i] == 'a' && st.top() == 'b'){
//             st.pop();
//             count++;
//         }
//         else{
//             st.push(s[i]);
//         }   
//     }
//     return count;
// }

// // Approach 2 : 
// int minimumDeletions(string s) {
//     int n = s.size();

//     vector<int> leftSide_b_Present(n, 0);
//     vector<int> rightSide_a_Present(n, 0);

//     int countB = 0;
//     for(int i=0; i<n; i++){
//         leftSide_b_Present[i] = countB;
//         if(s[i] == 'b'){
//             countB++;
//         }
//     }

//     // Similarly we can count the number of 'a' on the right side of the string
//     int countA = 0;
//     for(int i=n-1; i>=0; i--){
//         rightSide_a_Present[i] = countA;
//         if(s[i] == 'a'){
//             countA++;
//         }
//     }

//     int minDeletions = n; // Initialize with a large value
//     for(int i=0; i<n; i++){
//         minDeletions = min(minDeletions, leftSide_b_Present[i] + rightSide_a_Present[i]);
//     }
//     return minDeletions;
// }

// Approach 3 : Improving 2nd Approach
int minimumDeletions(string s) {
    int n = s.size();

    int countB = 0;
    for(int i=0; i<n; i++){
        if(s[i] == 'b'){
            countB++;
        }
    }

    int minDeletions = countB; // Initialize with the total count of 'b'
    int countA = 0;
    for(int i=n-1; i>=0; i--){
        if(s[i] == 'a'){
            countA++;
        }
        else{
            countB--;
        }
        minDeletions = min(minDeletions, countA + countB);
    }
    return minDeletions;
};

int main() {
    string s = "aababbab";
    cout << minimumDeletions(s) << endl; // Output: 2

    s = "bbaaaaabb";
    cout << minimumDeletions(s) << endl; // Output: 2

    return 0;
}