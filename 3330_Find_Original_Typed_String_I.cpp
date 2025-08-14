/*
Find the Original Typed String I - [Leetcode - 3330(Easy)]
------------------------------------------------------------
Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.

Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.

You are given a string word, which represents the final output displayed on Alice's screen.

Return the total number of possible original strings that Alice might have intended to type.

 

Example 1:

Input: word = "abbcccc"

Output: 5

Explanation:

The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".

Example 2:

Input: word = "abcd"

Output: 1

Explanation:

The only possible string is "abcd".

Example 3:

Input: word = "aaaa"

Output: 4

 

Constraints:

1 <= word.length <= 100
word consists only of lowercase English letters.
*/ 

#include <iostream>
using namespace std;

int possibleStringCount(string word) {
    int count = 0;

    for (int i = 1; i < word.length(); i++) {
        if (word[i] == word[i - 1]) count++;
    }

    return count + 1; //+1 for when Alice does no long press
}

int main() {
    string word = "abbcccc";
    cout << possibleStringCount(word) << endl;  // Output: 5
    return 0;
}