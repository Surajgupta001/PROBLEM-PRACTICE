/*
Lexicographical Numbers - [Leetcode - 386(Medium)]
---------------------------------------------------
Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

You must write an algorithm that runs in O(n) time and uses O(1) extra space. 

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:

Input: n = 2
Output: [1,2]
 

Constraints:
1 <= n <= 5 * 104
*/ 

#include <iostream>
#include <vector>
using namespace std;

void helper(int currNum, int n, vector<int>& result) {
    if(currNum > n) return;

    result.push_back(currNum);

    for(int append = 0; append <= 9; append++) {
        int nextNum = currNum * 10 + append;
        if(nextNum <= n) {
            helper(nextNum, n, result);
        }
    }
}

vector<int> lexicalOrder(int n) {
    vector<int> result;
    for(int startNum = 1; startNum <= 9; startNum++) {
        helper(startNum, n, result);
    }

    return result;
}

int main() {
    int n = 13;
    vector<int> result = lexicalOrder(n);
    for(int num : result) {
        cout << num << " ";
    }
    return 0;
}