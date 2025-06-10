/*
Maximum Difference Between Even and Odd Frequency I - [Leetcode - 3442(Easy)]]
-------------------------------------------------------------------------------
You are given a string s consisting of lowercase English letters.

Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in the string such that:

a1 has an odd frequency in the string.
a2 has an even frequency in the string.
Return this maximum difference.

Example 1:

Input: s = "aaaaabbc"

Output: 3

Explanation:

The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
The maximum difference is 5 - 2 = 3.

Example 2:

Input: s = "abcabcab"

Output: 1

Explanation:

The character 'a' has an odd frequency of 3, and 'c' has an even frequency of 2.
The maximum difference is 3 - 2 = 1.
 

Constraints:

3 <= s.length <= 100
s consists only of lowercase English letters.
s contains at least one character with an odd frequency and one with an even frequency.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int maxDifference(string s) {

    int n = s.length();
    vector<int> freq(26, 0);

    for(auto &ch : s){
        freq[ch - 'a']++;
    }

    int maxOddFreq = 0;
    int minEvenFreq = INT_MAX;

    for(int i = 0; i < 26; i++){
        if(freq[i] == 0) continue; // Skip characters with zero frequency
        if(freq[i] % 2 == 1) {
            // Odd frequency
            maxOddFreq = max(maxOddFreq, freq[i]);
        }
        else {
            // Even frequency
            minEvenFreq = min(minEvenFreq, freq[i]);
        }
    }

    return maxOddFreq - minEvenFreq;
}

int main() {
    string s1 = "aaaaabbc";
    cout << "Maximum difference for \"" << s1 << "\": " << maxDifference(s1) << endl;

    string s2 = "abcabcab";
    cout << "Maximum difference for \"" << s2 << "\": " << maxDifference(s2) << endl;

    return 0;
}