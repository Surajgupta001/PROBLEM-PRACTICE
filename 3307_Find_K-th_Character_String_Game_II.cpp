/*
Find the K-th Character in String Game II - [Leetcode - 3307(Hard)]
--------------------------------------------------------------------
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.

Now Bob will ask Alice to perform all operations in sequence:

If operations[i] == 0, append a copy of word to itself.
If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
Return the value of the kth character in word after performing all the operations.

Note that the character 'z' can be changed to 'a' in the second type of operation.

 

Example 1:

Input: k = 5, operations = [0,0,0]

Output: "a"

Explanation:

Initially, word == "a". Alice performs the three operations as follows:

Appends "a" to "a", word becomes "aa".
Appends "aa" to "aa", word becomes "aaaa".
Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
Example 2:

Input: k = 10, operations = [0,1,0,1]

Output: "b"

Explanation:

Initially, word == "a". Alice performs the four operations as follows:

Appends "a" to "a", word becomes "aa".
Appends "bb" to "aa", word becomes "aabb".
Appends "aabb" to "aabb", word becomes "aabbaabb".
Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".
 

Constraints:

1 <= k <= 1014
1 <= operations.length <= 100
operations[i] is either 0 or 1.
The input is generated such that word has at least k characters after all operations.
*/ 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

char kthCharacter(long long k, vector<int>& operations) {
        // Base case: If k is 1, the result is the initial character 'a'
        if (k == 1) {
            return 'a';
        }

        int n = operations.size();  // Size of the operations array
        int opType;                 // Store the operation type (0 or 1)
        long long len = 1;          // Start with length 1 (initial 'a')
        long long newK;             // To store the adjusted k value

        // Traverse through the operations array to determine the operation type
        for (int i = 0; i < n; i++) {
            len *= 2;               // Double the length at each step
            if (len >= k) {         // If the current length surpasses or equals k
                opType = operations[i];  // Get the current operation type
                newK = k - len / 2;      // Adjust k for the next recursive call
                break;                   // Break as we have found the required operation
            }
        }

        // Recursively find the character before the operation is applied
        char res = kthCharacter(newK, operations);
        
        // If operation type is 0, return the character as is
        if (opType == 0) 
            return res;

        // If operation type is 1, transform the character ('a' becomes 'b', etc.)
        if (res == 'z') 
            return 'a';  // Handle wrap-around from 'z' to 'a'
        
        return res + 1;   // Increment character by 1
    }