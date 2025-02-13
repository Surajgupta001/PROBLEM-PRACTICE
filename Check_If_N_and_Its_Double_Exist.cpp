/*
Check If N and Its Double Exists - [Leetcode - 1346(Easy)]
Given an array arr of integers, check if there exist two indices i and j such that :

i != j
0 <= i, j < arr.length
arr[i] == 2 * arr[j]

Example 1:

Input: arr = [10,2,5,3]
Output: true
Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]

Example 2:

Input: arr = [3,1,7,11]
Output: false
Explanation: There is no i and j that satisfy the conditions.
*/ 

#include <iostream>
#include <vector>
using namespace std;

bool checkIfExist(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(i != j and v[i] == 2 * v[j]){
                return true;
            }
        }
    }
    return false;
}

int main(){
    vector<int> v = {10,2,5,3};
    cout << boolalpha << checkIfExist(v) << endl;
    return 0;
}