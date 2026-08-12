/*
Find the String with LCP - [Leetcode - 2573(Hard)]
-------------------------------------------------------
We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:

lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.

Example 1:

Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
Output: "abab"
Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".

Example 2:

Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
Output: "aaaa"
Explanation: lcp corresponds to any 4 letter string with a single distinct letter. The lexicographically smallest of them is "aaaa". 

Example 3:

Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
Output: ""
Explanation: lcp[3][3] cannot be equal to 3 since word[3,...,3] consists of only a single letter; Thus, no answer exists. 

Constraints:

1 <= n == lcp.length == lcp[i].length <= 1000
0 <= lcp[i][j] <= n
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<int>> checkLCP(string &word) {
    int n = word.length();

    vector<vector<int>> lcp(n, vector<int>(n, 0));

    // Fill the last column of the lcp matrix
    for(int i=0; i<n; i++){
        lcp[i][n-1] = (word[i] == word[n-1]) ? 1 : 0;
    }

    // Fill the last row of the lcp matrix
    for(int j=0; j<n; j++){
        lcp[n-1][j] = (word[n-1] == word[j]) ? 1 : 0;
    }

    // Fill the rest of the lcp matrix based on the characters in the word
    for(int i=n-2; i>=0; i--){
        for(int j=n-2; j>=0; j--){
            if(word[i] == word[j]){
                lcp[i][j] = 1 + lcp[i+1][j+1];
            } else {
                lcp[i][j] = 0;
            }
        }
    }

    return lcp;
}

string findTheString(vector<vector<int>>& lcp) {
    int n = lcp.size();
    
    string word(n, '$'); // Initialize the word with placeholder characters

    // Fill the word based on the lcp matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if(lcp[i][j] != 0){ // If lcp[i][j] is not zero, it means word[i] and word[j] must be the same character
                word[i] = word[j];
                break;
            }
        }

        if(word[i] == '$'){ // If word[i] is still a placeholder, we need to assign it a character
            vector<bool> forbidden(26, false);
            for(int j=0; j<i; j++){
                if(lcp[i][j] == 0){ // If lcp[i][j] is zero, it means word[i] and word[j] must be different characters
                    forbidden[word[j] - 'a'] = true; // Mark the character of word[j] as forbidden for word[i]
                }
            }

            // Assign the smallest lexicographical character that is not forbidden
            for(int idx=0; idx<26; idx++){
                if(forbidden[idx] == false){ // If the character is not forbidden, we can assign it to word[i]
                    word[i] = idx + 'a'; // Assign the character to word[i]
                    break;
                }
            }

            // If we couldn't find a valid character for word[i], it means no valid string can be formed
            if(word[i] == '$'){
                return ""; // We never fill word[i]
            }
        }
    }

    return checkLCP(word) == lcp ? word : "";
}

int main() {
    vector<vector<int>> lcp = {{4,0,2,0},{0,3,0,1},{2,0,2,0},{0,1,0,1}};
    string result = findTheString(lcp);

    if(result.empty()){
        cout << "No valid string can be formed." << endl;
    } else {
        cout << "The lexicographically smallest string is: " << result << endl;
    }

    return 0;
}