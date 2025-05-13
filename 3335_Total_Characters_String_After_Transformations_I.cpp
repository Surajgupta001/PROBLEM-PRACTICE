/*
Total Characters in String After Transformations I - [Leetcode - 3335(Medium)]
------------------------------------------------------------------------------
You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:

If the character is 'z', replace it with the string "ab".
Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
Return the length of the resulting string after exactly t transformations.

Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:

Input: s = "abcyy", t = 2

Output: 7

Explanation:

First Transformation (t = 1):
'a' becomes 'b'
'b' becomes 'c'
'c' becomes 'd'
'y' becomes 'z'
'y' becomes 'z'
String after the first transformation: "bcdzz"
Second Transformation (t = 2):
'b' becomes 'c'
'c' becomes 'd'
'd' becomes 'e'
'z' becomes "ab"
'z' becomes "ab"
String after the second transformation: "cdeabab"
Final Length of the string: The string is "cdeabab", which has 7 characters.
Example 2:

Input: s = "azbk", t = 1

Output: 5

Explanation:

First Transformation (t = 1):
'a' becomes 'b'
'z' becomes "ab"
'b' becomes 'c'
'k' becomes 'l'
String after the first transformation: "babcl"
Final Length of the string: The string is "babcl", which has 5 characters.


Constraints:

1 <= s.length <= 105
s consists only of lowercase English letters.
1 <= t <= 105
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Map Approach
// Time Complexity: O(n*t) where n is the length of the string
int mod = 1e9 + 7;
int lengthAfterTransformations(string s, int t){
    int n = s.length();
    map<char, int> mp;

    for (auto &ch : s){
        mp[ch]++;
    }

    for (int count = 1; count <= t; count++){
        map<char, int> tempMap;

        for (auto &itr : mp){
            char ch = itr.first;
            int freq = itr.second;

            if (ch != 'z'){
                tempMap[ch + 1] = (tempMap[ch + 1] + freq) % mod;
            }
            else{
                tempMap['a'] = (tempMap['a'] + freq) % mod;
                tempMap['b'] = (tempMap['b'] + freq) % mod;
            }
        }
        mp = move(tempMap);
    }

    int ans = 0;
    for (auto &itr : mp){
        ans = (ans + itr.second) % mod;
    }
    return ans;
}

// Better Approach
// Time Complexity: O(n + t) where n is the length of the string
int mod = 1e9 + 7;
int lengthAfterTransformations(string str, int t){
    vector<int> freqMap(26, 0);

    for (int i = 0; i < str.size(); i++){
        freqMap[str[i] - 'a']++;
    }

    for (int count = 1; count < t; count++){
        vector<int> tempMap(26, 0); // Create a new vector to store updated counts

        for (int i = 0; i < 26; i++){
            char ch = 'a' + i;
            int freq = freqMap[i];

            if (ch != 'z'){
                tempMap[(ch + 1) - 'a'] = (tempMap[(ch + 1) - 'a'] + freq) % mod; // Increment the count of the next character
            }
            else{
                tempMap['a' - 'a'] = (tempMap['a' - 'a'] + freq) % mod; // Increment the count of 'a'
                tempMap['b' - 'a'] = (tempMap['b' - 'a'] + freq) % mod; // Increment the count of 'b'
            }
        }
        freqMap = move(tempMap); // Update the original map with the new counts
    }
    
    int ans = 0;
    for (int i = 0; i < 26; i++){
        ans = (ans + freqMap[i]) % mod; // Calculate the total length
    }
    return ans;
}

int main()
{
    string str = "abcyy";
    int t = 2;
    cout << lengthAfterTransformations(str, t) << endl; // Output: 7

    str = "azbk";
    t = 1;
    cout << lengthAfterTransformations(str, t) << endl; // Output: 5

    return 0;
}