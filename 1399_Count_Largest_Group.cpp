/*
Count Largest Group - [Leetcode - 1399(Easy)]
==============================================
You are given an integer n.

Each number from 1 to n is grouped according to the sum of its digits.

Return the number of groups that have the largest size.

 

Example 1:

Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
There are 4 groups with largest size.
Example 2:

Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.
 

Constraints:

1 <= n <= 104
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int countLargestGroup(int n) {
    unordered_map<int, int> digitSumCount;
    int maxCount = 0;
    int maxGroupCount = 0;

    for(int i=1; i<=n; i++){
        int sum = 0;
        int num = i;
        while(num > 0){
            sum += num % 10;
            num /= 10;
        }
        digitSumCount[sum]++;
        maxCount = max(maxCount, digitSumCount[sum]);
    }

    for(auto& pair : digitSumCount) {
        if(pair.second == maxCount) {
            maxGroupCount++;
        }
    }

    return maxGroupCount;
}

int main(){
        
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << countLargestGroup(n) << endl; // Output: 4
        
    return 0;
}