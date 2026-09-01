/*
Lexicographically Smallest Palindromic Permutation Greater Than Target - [Leetcode - 3734(Hard)]
-----------------------------------------------------------------------------------------------------
You are given two strings s and target, each of length n, consisting of lowercase English letters.

Return the lexicographically smallest string that is both a palindromic permutation of s and strictly greater than target. If no such permutation exists, return an empty string.

 

Example 1:

Input: s = "baba", target = "abba"

Output: "baab"

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
The lexicographically smallest permutation that is strictly greater than target is "baab".
Example 2:

Input: s = "baba", target = "bbaa"

Output: ""

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
Example 3:

Input: s = "abc", target = "abb"

Output: ""

Explanation:

s has no palindromic permutations. Therefore, the answer is "".

Example 4:

Input: s = "aac", target = "abb"

Output: "aca"

Explanation:

The only palindromic permutation of s is "aca".
"aca" is strictly greater than target. Therefore, the answer is "aca".
 

Constraints:

1 <= n == s.length == target.length <= 300
s and target consist of only lowercase English letters.
*/

// NOTE : SIMILAR PROBLEM TO 3720_Lexicographically_Smallest_Permutation_Greater_Than_Target.cpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool helper(string &curr, vector<int> &count, string &target, int index, bool strictGreater, string &result, int halfLen, char midChar) {

    // Base case: If we have constructed a string of the same length as half of the target
    if(curr.length() == halfLen){
        // Construct the full palindrome from the left half and the middle character (if any)
        string candidate = curr; // Left half of the palindrome
        string rightHalf = curr; // Right half of the palindrome
        reverse(rightHalf.begin(), rightHalf.end()); // Reverse the left half to form the right half
        
        // If there is a middle character, add it to the candidate
        if(midChar != '$'){ // If there is a middle character, add it to the candidate
            candidate.push_back(midChar); // Add the middle character if it exists
        }

        candidate += rightHalf; // Form the full palindrome

        if(candidate > target){ // Check if the candidate is strictly greater than target
            result = candidate; // Update the result
            return true; // Found a valid palindrome
        }

        return false; // Candidate is not greater than target
    }

    // Try to place each character in the current position
    for(char ch='a'; ch <= 'z'; ch++){
        if(count[ch - 'a'] == 0) continue; // If we don't have any more of this character, skip it
        if(!strictGreater && ch < target[index]) continue; // If we haven't placed a character greater than target yet, and this character is less than the target character at this index, skip it

        // DO
        curr += ch;
        count[ch - 'a']--;

        // EXPLORE
        bool isGreater = strictGreater || ch > target[index];
        if(helper(curr, count, target, index + 1, isGreater, result, halfLen, midChar)) {
            return true; // If we found a valid permutation, return true
        }

        // UNDO
        curr.pop_back();
        count[ch - 'a']++;
    }
    return false;
}

string lexPalindromicPermutation(string s, string target) {
    int n = s.length();
    vector<int> count(26, 0);

    // Count the frequency of each character in s
    for(char &ch : s) {
        count[ch - 'a']++;
    }

    int oddCount = 0; // Count of characters with odd frequency
    char midChar = '$'; // Character that will be in the middle of the palindrome (if any)

    for(int c=0; c<26; c++){
        if(count[c] % 2 == 1) {
            oddCount++;
            midChar = c + 'a'; // Update the middle character
        }
    }

    // If there are more than one character with odd frequency, a palindromic permutation is not possible
    if(oddCount > 1) {
        return ""; // No palindromic permutation possible
    }

    // Construct the first half of the palindrome
    int halfLen = 0;
    string result = "";

    for(int c=0; c<26; c++){
        count[c] /= 2; // We only need half of the characters for the first half of the palindrome
    }

    halfLen = n/2;

    string curr; // Left Half
    helper(curr, count, target, 0, false, result, halfLen, midChar);

    return result;
}

int main() {
    string s = "baba";
    string target = "abba";

    string result = lexPalindromicPermutation(s, target);
    if(result.empty()) {
        cout << "No palindromic permutation of s is lexicographically greater than target." << endl;
    } else {
        cout << "The lexicographically smallest palindromic permutation of s that is strictly greater than target is: " << result << endl;
    }

    return 0;
}