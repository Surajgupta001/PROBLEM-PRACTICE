/*
Find the K-th Character in String Game I - [Leetcode - 3304(Easy)]
--------------------------------------------------------------------
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k.

Now Bob will ask Alice to perform the following operation forever:

Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".

Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.

Note that the character 'z' can be changed to 'a' in the operation.

 

Example 1:

Input: k = 5

Output: "b"

Explanation:

Initially, word = "a". We need to do the operation three times:

Generated string is "b", word becomes "ab".
Generated string is "bc", word becomes "abbc".
Generated string is "bccd", word becomes "abbcbccd".
Example 2:

Input: k = 10

Output: "c"

 

Constraints:

1 <= k <= 500
*/

#include <iostream>
#include <string>
using namespace std;

// Naive Approach
char kthCharacter(int k) {
    string word = "a";
    while (word.length() < k) {
        string next = "";
        for (char c : word) {
            next += (c == 'z') ? 'a' : c + 1;
        }
        word += next;
    }
    return word[k - 1];
}

// Better Approach
char kthCharacter(int k) {
    int shift = __builtin_popcount(k - 1);
    return 'a' + shift;
}

int main() {
    int k;
    cout << "Enter the value of k: ";
    cin >> k;
    char result = kthCharacter(k);
    cout << "The " << k << "-th character is: " << result << endl;
    return 0;
}