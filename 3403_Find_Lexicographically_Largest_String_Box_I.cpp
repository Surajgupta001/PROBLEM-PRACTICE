/*
Find the Lexicographically Largest String From the Box I - [Leetcode - 3403(Medium)]
-------------------------------------------------------------------------------------
You are given a string word, and an integer numFriends.

Alice is organizing a game for her numFriends friends. There are multiple rounds in the game, where in each round:

word is split into numFriends non-empty strings, such that no previous round has had the exact same split.
All the split words are put into a box.
Find the lexicographically largest string from the box after all the rounds are finished.

 

Example 1:

Input: word = "dbca", numFriends = 2

Output: "dbc"

Explanation: 

All possible splits are:

"d" and "bca".
"db" and "ca".
"dbc" and "a".

Example 2:

Input: word = "gggg", numFriends = 4

Output: "g"

Explanation: 

The only possible split is: "g", "g", "g", and "g".

 

Constraints:

1 <= word.length <= 5 * 103
word consists only of lowercase English letters.
1 <= numFriends <= word.length
*/ 

#include <iostream>
#include <string>
using namespace std;

string answerString(string word, int numFriends) {
    int n = word.size();

    if(numFriends == 1) return word;

    string result = "";

    int largestPossible = n - (numFriends - 1);
    
    for(int i=0; i<n; i++){
        int canTakenLength = min(largestPossible, n - i);

        result = max(result, word.substr(i, canTakenLength));
    }
    return result;
}

int main() {

    string word;
    int numFriends;

    cout << "Enter the word: ";
    cin >> word;
    cout << "Enter the number of friends: ";
    cin >> numFriends;

    string result = answerString(word, numFriends);
    cout << "The lexicographically largest string from the box is: " << result << endl;

    return 0;
}