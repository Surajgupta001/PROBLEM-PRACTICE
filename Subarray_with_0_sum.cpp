/*
Subarray with 0 sum - gfg
==========================
Given an array of positive and negative numbers, the task is to find if there is a subarray (of size at least one) with 0 sum.

Examples: 

Input: {4, 2, -3, 1, 6}
Output: true 
Explanation:
There is a subarray with zero sum from index 1 to 3.

Input: {4, 2, 0, 1, 6}
Output: true
Explanation: The third element is zero. A single element is also a sub-array.

Input: {-3, 2, 3, 1, 6}
Output: false
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool subArrayExists(vector<int>&v, int n){
    /*
    Time and Space Complexity: O(n)
    */ 
    unordered_set<int>set;
    int sum = 0;
    for(int i=0;i<n;i++){
        sum += v[i];
        if(sum == 0 or set.find(sum) != set.end()) return true;
        set.insert(sum);
    }
    return false;
}

int main(){
    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    cout<<"Enter all the elements of vector: ";
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];

    cout<<boolalpha<<subArrayExists(v,n)<<endl;
    return 0;
}