/*
Find N Unique Integers Sum up to Zero - [Leetcode - 1304(Easy)]
-----------------------------------------------------------------
Given an integer n, return any array containing n unique integers such that they add up to 0.

Example 1:

Input: n = 5
Output: [-7,-1,1,3,4]
Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

Example 2:

Input: n = 3
Output: [-1,0,1]
Example 3:

Input: n = 1
Output: [0]
 
Constraints:

1 <= n <= 1000

*/ 

#include <iostream>
#include <vector>
using namespace std;

vector<int> sumZero(int n) {
    vector<int> result;
    for (int i = 1; i <= n / 2; i++) {
        result.push_back(i);
        result.push_back(-i);
    }
    if (n % 2 == 1) {
        result.push_back(0);
    }
    return result;
}

vector<int> sumZero(int n){
    vector<int> result(n);
    
    int start = 1;
    int i = 0;
    
    while(i+1 < n){
        result[i] = start;
        result[i+1] = -start;
        i += 2;
        start++;
    }

    return result;
}

vector<int> sumZero(int n){
    vector<int> result(n);
    int i = 0;
    int j = n-1;
    int start = 1;

    while(i < j){
        result[i] = start;
        result[j] = -start;
        i++;
        j--;
    }

    return result;
}

int main() {
    int n = 5;
    vector<int> result = sumZero(n);
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}