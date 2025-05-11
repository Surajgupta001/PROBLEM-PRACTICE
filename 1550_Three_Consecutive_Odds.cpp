/*
Three Consecutive Odds - [Leetcode - 1550(Easy)]
-------------------------------------------------
Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.

Example 1:

Input: arr = [2,6,4,1]
Output: false
Explanation: There are no three consecutive odds.
Example 2:

Input: arr = [1,2,34,3,4,5,7,23,12]
Output: true
Explanation: [5,7,23] are three consecutive odds.
 

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 1000
*/ 

#include <iostream>
#include <vector>
using namespace std;

bool threeConsecutiveOdds(vector<int>& arr) {
    int count = 0;
    
    for(int i=0; i<arr.size(); i++){
        if(arr[i] % 2 != 0){
            count++;
            if(count == 3){
                return true;
            }
        }
        else{
            count = 0; // Reset count if an even number is found
        }
    }
    return false; // Return false if no three consecutive odds are found
}

int main(){
    vector<int> arr = {1, 2, 34, 3, 4, 5, 7, 23, 12};
    cout << (threeConsecutiveOdds(arr) ? "true" : "false") << endl; // Output: true

    arr = {2, 6, 4, 1};
    cout << (threeConsecutiveOdds(arr) ? "true" : "false") << endl; // Output: false

    return 0;
}