/*
Longest Substring of One Repeating Character - [Leetcode - 2213(Hard)]
-------------------------------------------------------------------------
You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.

The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].

Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.

Example 1:

Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
Output: [3,3,4]
Explanation: 
- 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
- 2nd query updates s = "bbbccc". 
  The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
- 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
Thus, we return [3,3,4].

Example 2:

Input: s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
Output: [2,3]
Explanation:
- 1st query updates s = "abazz". The longest substring consisting of one repeating character is "zz" with length 2.
- 2nd query updates s = "aaazz". The longest substring consisting of one repeating character is "aaa" with length 3.
Thus, we return [2,3].

Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.
k == queryCharacters.length == queryIndices.length
1 <= k <= 10^5
queryCharacters consists of lowercase English letters.
0 <= queryIndices[i] < s.length
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class node {
public:
    int prefix = 0;
    int suffix = 0;
    int maxLength = 0;
    int leftMostChar = 0;
    int rightMostChar = 0;

    // Default Constructor
    node() {
        prefix = 0;
        suffix = 0;
        maxLength = 0;
        leftMostChar = 0;
        rightMostChar = 0;
    }

    // Constructor
    node(int prefix, int suffix, int maxLength, int leftMostChar, int rightMostChar) {
        this->prefix = prefix;
        this->suffix = suffix;
        this->maxLength = maxLength;
        this->leftMostChar = leftMostChar;
        this->rightMostChar = rightMostChar;
    }

    // Merge two nodes
    node merge(node &left, node &right, int leftLen, int rightLen) {
        node result;

        result.leftMostChar = left.leftMostChar;
        result.rightMostChar = right.rightMostChar;

        // Prefix
        result.prefix = left.prefix;

        if (left.prefix == leftLen && left.rightMostChar == right.leftMostChar) {
            result.prefix += right.prefix;
        }

        // Suffix
        result.suffix = right.suffix;

        if (right.suffix == rightLen && left.rightMostChar == right.leftMostChar) {
            result.suffix += left.suffix;
        }

        // Max Length
        result.maxLength = max(left.maxLength, right.maxLength);

        if (left.rightMostChar == right.leftMostChar) {
            result.maxLength = max(result.maxLength, left.suffix + right.prefix);
        }

        return result;
    }

    // Build Segment Tree
    void buildSegmentTree(int idx, int left, int right, string &s, vector<node> &segTree) {
        if (left == right) {
            segTree[idx] = node(1, 1, 1, s[left], s[left]);
            return;
        }

        int mid = left + (right - left) / 2;

        buildSegmentTree(2 * idx + 1, left, mid, s, segTree);

        buildSegmentTree(2 * idx + 2, mid + 1, right, s, segTree);

        segTree[idx] = merge(segTree[2 * idx + 1], segTree[2 * idx + 2], mid - left + 1, right - mid);
    }

    // Update Segment Tree
    void updateSegmentTree(int idx, int left, int right, int position, char ch, vector<node> &segTree) {
        if (left == right) {
            segTree[idx] = node(1, 1, 1, ch, ch);
            return;
        }

        int mid = left + (right - left) / 2;

        if (position <= mid) {
            updateSegmentTree(2 * idx + 1, left, mid, position, ch, segTree);
        } else {
            updateSegmentTree(2 * idx + 2, mid + 1, right, position, ch, segTree);
        }

        segTree[idx] = merge(segTree[2 * idx + 1], segTree[2 * idx + 2], mid - left + 1, right - mid);
    }
};

// Function to process the queries and return the lengths of the longest substring of one repeating character after each query
vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
    int n = s.length();

    vector<node> segTree(4 * n, node());

    node obj;

    obj.buildSegmentTree(0, 0, n - 1, s, segTree);

    int k = queryIndices.size();

    vector<int> result(k);

    for (int i = 0; i < k; i++) {
        int index = queryIndices[i];
        char ch = queryCharacters[i];

        obj.updateSegmentTree(0, 0, n - 1, index, ch, segTree);

        result[i] = segTree[0].maxLength;
    }

    return result;
}

int main() {
    string s = "babacc";
    string queryCharacters = "bcb";
    vector<int> queryIndices = {1, 3, 3};

    vector<int> result = longestRepeating(s, queryCharacters, queryIndices);

    for (int length : result) {
        cout << length << " ";
    }
    cout << endl;

    return 0;
}