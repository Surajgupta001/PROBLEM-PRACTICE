/*
Lexicographically Smallest Permutation Greater Than Target - [Leetcode - 3720(Medium)]
----------------------------------------------------------------------------------------
You are given two strings s and target, both having length n, consisting of lowercase English letters.

Return the lexicographically smallest permutation of s that is strictly greater than target. If no permutation of s is lexicographically strictly greater than target, return an empty string.

A string a is lexicographically strictly greater than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b.

Example 1:

Input: s = "abc", target = "bba"

Output: "bca"

Explanation:

The permutations of s (in lexicographical order) are "abc", "acb", "bac", "bca", "cab", and "cba".
The lexicographically smallest permutation that is strictly greater than target is "bca".
Example 2:

Input: s = "leet", target = "code"

Output: "eelt"

Explanation:

The permutations of s (in lexicographical order) are "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
The lexicographically smallest permutation that is strictly greater than target is "eelt".
Example 3:

Input: s = "baba", target = "bbaa"

Output: ""

Explanation:

The permutations of s (in lexicographical order) are "aabb", "abab", "abba", "baab", "baba", and "bbaa".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
 

Constraints:

1 <= s.length == target.length <= 300
s and target consist of only lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int helper(string &curr, vector<int> &count, string &target, int index, bool strictGreater, string &result) {
    // Base case: If we have constructed a string of the same length as target
    if(index == target.length()){
        if(strictGreater){ // If we have constructed a string that is greater than target, return it
            result = curr;
            return true;
        } else {
            return false; // If we have constructed a string that is not greater than target, return false
        }
    }

    // Try to place each character in the current position
    for(char ch='a'; ch <= 'z'; ch++){
        if(count[ch - 'a'] == 0) continue; // If we don't have any more of this character, skip it
        if(strictGreater ==  false && ch < target[index]) continue; // If we haven't placed a character greater than target yet, and this character is less than the target character at this index, skip it
        
        // DO
        count[ch - 'a']--;
        curr += ch;

        // EXPLORE
        bool isGreater = strictGreater || ch > target[index];
        
        if(helper(curr, count, target, index + 1, isGreater, result)) {
            return true; // If we found a valid permutation, return true
        }
        
        // UNDO
        curr.pop_back();
        count[ch - 'a']++;
    }
    return false;
}

string lexGreaterPermutation(string s, string target) {
    vector<int> count(26, 0);
    
    for(auto &ch : s) {
        count[ch - 'a']++;
    }

    string curr;
    string result = "";

    helper(curr, count, target, 0, false, result);
    return result;
}

int main() {
    string s = "abc";
    string target = "bba";

    string result = lexGreaterPermutation(s, target);
    if(result.empty()) {
        cout << "No permutation of s is lexicographically greater than target." << endl;
    } else {
        cout << "The lexicographically smallest permutation of s that is strictly greater than target is: " << result << endl;
    }

    return 0;
}