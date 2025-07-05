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
    if(k == 1) return 'a'; // Base case, the first character is always 'a'

    int n = operations.size();
    long long length = 1; // Initial length of the string "a"
    long long newK = 0;
    int operationType = -1;

    for(int i=0; i<n; i++) {
        length *= 2; // Each operation doubles the length of the string
        if(length >= k) {
            operationType = operations[i];
            newK = k - length / 2;
            break;
        }
    }

    char ch = kthCharacter(newK, operations); // Recursive call to find the k-th character in the reduced string

    if(operationType == 0) {
        return ch;
    }
    else {
        return (ch == 'z') ? 'a' : ch + 1;
    }
}

int main() {
    long long k = 5;
    vector<int> operations = {0, 0, 0};

    char result = kthCharacter(k, operations);
    cout << result << endl;

    return 0;
}