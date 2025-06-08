/*
Lexicographically Minimum String After Removing Stars - [Leetcode - 3170(Medium)]
-----------------------------------------------------------------------------------
You are given a string s. It may contain any number of '*' characters. Your task is to remove all '*' characters.

While there is a '*', do the following operation:

Delete the leftmost '*' and the smallest non-'*' character to its left. If there are several smallest characters, you can delete any of them.
Return the lexicographically smallest resulting string after removing all '*' characters.

Example 1:

Input: s = "aaba*"

Output: "aab"

Explanation:

We should delete one of the 'a' characters with '*'. If we choose s[3], s becomes the lexicographically smallest.

Example 2:

Input: s = "abc"

Output: "abc"

Explanation:

There is no '*' in the string.

*/ 

#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Custom comparator for the priority queue
// It ensures the smallest character (lexicographically) comes first.
// If characters are equal, the one with the smaller index comes first.
class custom_comparator {
public:
    bool operator()(const pair<char, int>& p1, const pair<char, int>& p2) {
        if(p1.first == p2.first) {
            return p1.second < p2.second;
        }
        return p1.first > p2.first;
    }
};

// Function to remove all '*' and the smallest character to the left of each '*'
string clearStars(string s) {
    int n = s.length();

    // Priority queue to keep track of smallest characters and their indices
    priority_queue<pair<char, int>, vector<pair<char, int>>, custom_comparator> pq;

    // Traverse the string
    for(int i = 0; i < n; i++){
        if(s[i] != '*') {
            // Push non-'*' characters with their indices into the priority queue
            pq.push({s[i], i});
        }
        else {
            // For '*', remove the smallest character to its left
            int idx = pq.top().second;
            pq.pop();
            s[idx] = '*'; // Mark the character to be removed
        }
    }

    // Build the result string without '*' characters
    string result = "";
    for(int i = 0; i < n; i++) {
        if(s[i] != '*') {
            result.push_back(s[i]);
        }
    }
    return result;
}

/*
==================== Custom Comparator By using function ================
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Comparator function for priority_queue
bool custom_comparator(const pair<char, int>& p1, const pair<char, int>& p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first > p2.first;
}

// Function to remove all '*' and the smallest character to the left of each '*'
string clearStars(string s) {
    int n = s.length();

    // Use function pointer as comparator
    priority_queue<pair<char, int>, vector<pair<char, int>>, bool(*)(const pair<char, int>&, const pair<char, int>&)> pq(custom_comparator);

    // Traverse the string
    for(int i = 0; i < n; i++){
        if(s[i] != '*') {
            // Push non-'*' characters with their indices into the priority queue
            pq.push({s[i], i});
        }
        else {
            // For '*', remove the smallest character to its left
            int idx = pq.top().second;
            pq.pop();
            s[idx] = '*'; // Mark the character to be removed
        }
    }

    // Build the result string without '*' characters
    string result = "";
    for(int i = 0; i < n; i++) {
        if(s[i] != '*') {
            result.push_back(s[i]);
        }
    }
    return result;
}

int main() {
    string s;
    cout << "Enter the string: ";
    cin >> s;

    string result = clearStars(s);
    cout << "Resulting string after removing stars: " << result << endl;

    return 0;
}
*/ 

int main() {
    string s;
    cout << "Enter the string: ";
    cin >> s;

    string result = clearStars(s);
    cout << "Resulting string after removing stars: " << result << endl;

    return 0;
}