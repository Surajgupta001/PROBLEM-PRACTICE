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

// O(n^2) 
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

int bestStartingPoint(string word, int n) {
    int i = 0; // Best Starting point of the first substring
    int j = 1; // Keep moving to find the best starting point of the second substring

    while(j < n){
        int k = 0; // Length of the common prefix between the two substrings starting at i and j
        
        while(i + k < n && j + k < n && word[i + k] == word[j + k]) { // Compare characters at the current position and the next position
            k++; // Increment the length of the common prefix
        }

        if(j + k < n && (i + k >= n || word[j + k] > word[i + k])) {
            // If the next character of the second substring is greater than the first substring
            i = j; // Update the best starting point to the current position
            j = j + 1; // Move to the next position
        }
        else{
            // If the next character of the first substring is greater than or equal to the second substring
            j = j + k + 1; // Move to the next position after the common prefix
        }
    }
    return i; // Return the best starting point of the first substring
}
// Better Approach: O(n) and space complexity O(1)
string answerString(string word, int numFriends) {
    int n = word.size();

    if(numFriends == 1) return word;

    int i = bestStartingPoint(word, n);

    int longestPossibleLength = n - (numFriends - 1);

    int canTakenLength = min(longestPossibleLength, n - i);
    
    return word.substr(i, canTakenLength); // Return the substring starting from the best starting point with the maximum
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