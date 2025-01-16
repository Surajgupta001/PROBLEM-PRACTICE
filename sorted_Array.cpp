/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].

Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> sortedSquare(vector<int>& v){

    vector<int> ans;

    int left_ptr = 0;
    int right_ptr = v.size() - 1;

    while (left_ptr <= right_ptr){
        if (abs(v[left_ptr]) < abs(v[right_ptr])){
            ans.push_back(v[right_ptr] * v[right_ptr]);
            right_ptr--;
        } else {
            ans.push_back(v[left_ptr] * v[left_ptr]);
            left_ptr++;
        }
    }
    return ans;
}

int main(){

    int n;
    cout<<"Enter the size of array: ";
    cin>>n;

    cout<<"Enter all the elements of vectors: ";
    vector<int>v(n);
    for (int i=0;i<n;i++) {
        cin>>v[i];
    }

    vector<int> result = sortedSquare(v);

    cout<<"Square Sorted Array: ";
    for (int i=result.size()-1; i>=0;i--) {
        cout<<result[i]<<" ";
    }
    cout << endl;

    return 0;
}