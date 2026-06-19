/*
Process String with Special Operations II - [Leetcode - 3614(Hard)]
---------------------------------------------------------------------

You are given a string s consisting of lowercase English letters and the special characters: '*', '#', and '%'.

You are also given an integer k.

Build a new string result by processing s according to the following rules from left to right:

If the letter is a lowercase English letter append it to result.
A '*' removes the last character from result, if it exists.
A '#' duplicates the current result and appends it to itself.
A '%' reverses the current result.
Return the kth character of the final string result. If k is out of the bounds of result, return '.'.

Example 1:

Input: s = "a#b%*", k = 1

Output: "a"

Explanation:

i	s[i]	Operation	Current result
0	'a'	Append 'a'	"a"
1	'#'	Duplicate result	"aa"
2	'b'	Append 'b'	"aab"
3	'%'	Reverse result	"baa"
4	'*'	Remove the last character	"ba"
The final result is "ba". The character at index k = 1 is 'a'.

Example 2:

Input: s = "cd%#*#", k = 3

Output: "d"

Explanation:

i	s[i]	Operation	Current result
0	'c'	Append 'c'	"c"
1	'd'	Append 'd'	"cd"
2	'%'	Reverse result	"dc"
3	'#'	Duplicate result	"dcdc"
4	'*'	Remove the last character	"dcd"
5	'#'	Duplicate result	"dcddcd"
The final result is "dcddcd". The character at index k = 3 is 'd'.

Example 3:

Input: s = "z*#", k = 0

Output: "."

Explanation:

i	s[i]	Operation	Current result
0	'z'	Append 'z'	"z"
1	'*'	Remove the last character	""
2	'#'	Duplicate the string	""
The final result is "". Since index k = 0 is out of bounds, the output is '.'.

Constraints:

1 <= s.length <= 10^5
s consists of only lowercase English letters and special characters '*', '#', and '%'.
0 <= k <= 10^15
The length of result after processing s will not exceed 10^15.
*/

#include <iostream>
#include <string>
using namespace std;

char processStr(string s, long long k) {
    int n = s.length();

    long long l = 0;

    for(auto &ch : s){
        if(ch == '*'){
            if(l > 0){
                l--;
            }
        } else if(ch == '#'){
            l *= 2;
        } else if(ch == '%'){
            // do nothing
            // Reverse does not change the length of the string
            continue;
        } else {
            l++;
        }
    }

    if(k >= l){
        return '.';
    }

    for(int i=n-1; i>=0; i--){
        if(s[i] == '*'){
            // no change in k
            l++;
        } else if(s[i] == '%'){
            // no change in l
            k = l - 1 - k; // reverse the string, so we need to find the character at index l-1-k
        } else if(s[i] == '#'){
            l = l/2;
            k = (k >= l) ? (k - l) : k; // if k is greater than or equal to l, we need to find the character at index k-l in the first half of the string
        } else {
            // 'a' to 'z'
            l--;
        }

        if(k == l){
            return s[i];
        }
    }
    return '.';
}

int main() {
    string s = "a#b%*";
    cout << processStr(s, 1) << endl; // Output: "a"

    s = "z*#";
    cout << processStr(s, 0) << endl; // Output: "."

    return 0;
}