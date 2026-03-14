/*
The k-th Lexicographical String of All Happy Strings of Length n - [Leetcode - 1415(Medium)]
-----------------------------------------------------------------------------------------------
A happy string is a string that:

consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

Example 1:

Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".

Example 2:

Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.

Example 3:

Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
 

Constraints:

1 <= n <= 10
1 <= k <= 100
*/ 

// NOTE : Generating all possible sequences of length n => Backtracking approach

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

void backtracking(int n, int k, string curr, vector<string>& happyStrings) {
    if (curr.length() == n) {
        happyStrings.push_back(curr);
        return;
    }
    
    for (char c : {'a', 'b', 'c'}) {
        if (curr.empty() || curr.back() != c) {
            // BACKTRACKING STEPS
            curr.push_back(c); // DO 
            backtracking(n, k, curr, happyStrings); // EXPLORE
            curr.pop_back(); // UNDO
        }
    }
}

string getHappyString(int n, int k) {
    string curr = "";
    
    vector<string> happyStrings;
    
    backtracking(n, k, curr, happyStrings);
    
    if (happyStrings.size() < k) {
        return "";
    }
    return happyStrings[k - 1];
}

// Slightly optimized version without storing all happy strings in a vector
string getHappyString(int n, int k) {
    string curr = "";
    
    int count = 0;
    
    function<void()> backtracking = [&]() {
        if (curr.length() == n) {
            count++;
            return;
        }
        
        for (char c : {'a', 'b', 'c'}) {
            if (curr.empty() || curr.back() != c) {
                // BACKTRACKING STEPS
                curr.push_back(c); // DO 
                backtracking(); // EXPLORE
                if (count == k) {
                    return; // Early exit if we have found the k-th happy string
                }
                curr.pop_back(); // UNDO
            }
        }
    };
    
    backtracking();
    
    return count < k ? "" : curr;
}

int main () {
    int n = 1, k = 3;
    cout << getHappyString(n, k) << endl; // Output: "c"

    n = 1, k = 4;
    cout << getHappyString(n, k) << endl; // Output: ""

    n = 3, k = 9;
    cout << getHappyString(n, k) << endl; // Output: "cab"

    return 0;
}