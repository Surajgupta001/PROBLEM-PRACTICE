/*
Given two sorted array arr1 and arr2 of size m amd n respectively, return the median of two sorted array.

Time Complexity : O(log(m+n))

INPUT: Num1:[1,3] , Num2:[2]
OUTPUT: 2.000

INPUT: Num1:[1,2] , Num2:[3,4]
OUTPUT: 2.5000
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double medianSortedArray(vector<int>&v1, vector<int>&v2){

    vector<int>ans;

    // merging two vectors
    ans.reserve(v1.size() + v2.size());

    // inserting ans vector
    ans.insert(ans.end(),v1.begin(),v1.end());
    ans.insert(ans.end(),v2.begin(),v2.end());

    // sorting two vector
    sort(ans.begin(),ans.end());

    // If the size is even, the median is the average of the two middle elements.
    if(ans.size()%2 == 0){
        return (ans[ans.size()/2 - 1] + ans[ans.size()/2])/2;
    }
    // If the size is odd, the median is the middle element
    else{
        return ans[ans.size()/2];
    }
}
int main(){

    int m;
    cout<<"Enter the size of 1st vector: ";
    cin>>m;

    vector<int>v1(m);
    for(int i=0;i<m;i++){
        cin>>v1[i];
    }

    int n;
    cout<<"Enter the size of 2nd vector: ";
    cin>>n;

    vector<int>v2(n);
    for(int i=0;i<n;i++){
        cin>>v2[i];
    }

    double median = medianSortedArray(v1,v2);

    cout<<"Median is: "<<median<<endl;
    
    return 0;
}