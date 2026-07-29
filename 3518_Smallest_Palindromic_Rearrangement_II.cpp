/*
Smallest Palindromic Rearrangement II - [Leetcode - 3518(Hard)]
-------------------------------------------------------------------

You are given a palindromic string s and an integer k.

Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.

Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.

Example 1:

Input: s = "abba", k = 2

Output: "baab"

Explanation:

The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
Example 2:

Input: s = "aa", k = 2

Output: ""

Explanation:

There is only one palindromic rearrangement: "aa".
The output is an empty string since k = 2 exceeds the number of possible rearrangements.
Example 3:

Input: s = "bacab", k = 1

Output: "abcba"

Explanation:

The two distinct palindromic rearrangements of "bacab" are "abcba" and "bacab".
Lexicographically, "abcba" comes before "bacab". Since k = 1, the output is "abcba".
 

Constraints:

1 <= s.length <= 10^4
s consists of lowercase English letters.
s is guaranteed to be palindromic.
1 <= k <= 10^6
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long nCr(int n, int r, int K) {
    // nCr == nC(n-r) -> both are same
    // 5C3 = 5C2
    // 5C2 = 5C(5-2) = 5C3
    r = min(r, n - r); // nCr == nC(n-r)

    long long result = 1;
    for(int i=1; i<=r; i++){ // O(log2(k))
        result = result * (n - r + i) / i; // result is becoimg twice

        if(result >= K){ // if result exceeds K, we can stop calculating further
            return result;
        }
    }
    return result;
}

string smallestPalindrome(string s, int k) {
    int n = s.length();
    char mid = '\0';

    if(n % 2 == 1){ // odd length
        mid = s[n/2]; // the middle character will be fixed in the middle of the palindrome
    }

    vector<int> count(26, 0); // frequency of each character
    for(int i=0; i<n; i++){
        if(n % 2 == 1 && i == n/2) continue; // mid character reserved for middle one
        count[s[i]-'a']++; // counting the frequency of each character
    }

    // Half Frequency will be used to build halfResult
    for(int i=0; i<26; i++){
        count[i] /= 2;
    }

    string halfResult = "";
    int half = n/2;

    // Building the halfResult string in lexicographical order
    for(int i=0; i<half; i++){ // O(n/2)
        // I am trying to fill ith position
        // what if I could never fill a character in ith position, then I will return empty string
        bool placedCharacter = false; // in ith position
        
        for(int j=0; j<26; j++){
            if(count[j] > 0){
                count[j] -= 1;

                // Count number of ways
                long long ways = 1;
                int letters = 0;
                for(int c=0; c<26; c++){
                    letters += count[c];
                }

                for(int c=0; c<26; c++){
                    if(count[c] > 0){
                        ways *= nCr(letters, count[c], k); // O(log2(k))
                        letters -= count[c];
                    }

                    if(ways >= k){
                        break;
                    }
                }

                if(ways >= k){ // this block contain my kth one
                    halfResult.push_back(j + 'a'); // fixed this character at ith position
                    placedCharacter = true;
                    break;
                }

                k -= ways; // when k >= ways
                count[j] += 1; // restore the count
            }
        }

        if(!placedCharacter){
            return ""; // if I could not place any character in ith position, then return empty string
        }
    }

    // halfResult + mid + reverse(halfResult) will give the final result
    string revHalfResult = halfResult;
    reverse(revHalfResult.begin(), revHalfResult.end()); // O(n/2)

    if(mid != '\0'){
        halfResult.push_back(mid);
    }

    return halfResult + revHalfResult;
}

int main() {
    string s = "abba";
    int k = 2;
    string result = smallestPalindrome(s, k);
    cout << result << endl;
    return 0;
}