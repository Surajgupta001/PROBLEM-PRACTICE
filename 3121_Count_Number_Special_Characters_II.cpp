/*
Count the Number of Special Characters I - [Leetcode - 3121(Medium)]
----------------------------------------------------------------------

You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.

Return the number of special letters in word.

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

There are no special characters in word.

Example 3:

Input: word = "AbBCab"

Output: 0

Explanation:

There are no special characters in word.

Constraints:

1 <= word.length <= 2 * 10^5
word consists of only lowercase and uppercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Approach (Track last occurrence of lowercase and first occurrence of uppercase)
//T.C : O(n)
//S.C : O(1) - fixed-size arrays of length 26
int numberOfSpecialChars(string word) {
    vector<int> lastSmall(26, -1);
    vector<int> firstCapital(26, -1);

    for(int i=0; i<word.size(); i++){
        char ch = word[i];

        if(islower(ch)){
            lastSmall[ch - 'a'] = i;
        } else {
            firstCapital[ch - 'A'] = (firstCapital[ch - 'A'] == -1) ? i : firstCapital[ch - 'A'];
        }
    }

    int count = 0;
    
    for(int i=0; i<26; i++){
        if(lastSmall[i] != -1 && firstCapital[i] != -1 && lastSmall[i] < firstCapital[i]){
            count++;
        }
    }
    return count;
}

int main() {
    string word1 = "aaAbcBC";
    cout << numberOfSpecialChars(word1) << endl; // Output: 3

    string word2 = "abc";
    cout << numberOfSpecialChars(word2) << endl; // Output: 0

    string word3 = "AbBCab";
    cout << numberOfSpecialChars(word3) << endl; // Output: 0

    return 0;
}