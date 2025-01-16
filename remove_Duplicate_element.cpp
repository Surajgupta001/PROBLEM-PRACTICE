/*
Write a program to remove dublicate elements in an array.

INPUT: arr = [1,1,2]
OUTPUT:2, arr = [1,2]

INPUT: arr = [0,0,1,1,1,2,2,3,3,4]
OUTPUT:5, arr = [0,1,2,3,4]
*/ 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int removeDublicate(vector<int>&v){
    /*
    * Time: O(n(logn))
    * Space: O(1)
    */ 
    if(v.size() == 0){
        return 0;
    }

    int index = 0;
    for(int i=0;i<v.size();i++){
        if(v[i] != v[index]){
            index++;
            v[index] = v[i];
        }
    }

    v.erase(v.begin()+index+1,v.end());

    return index+1;
}
int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;
    
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    int newArray = removeDublicate(v);
    cout<<"New array after removing duplicates element: ";
    for(int i=0;i<newArray;i++){
        cout<<v[i]<<" ";
    }
    
    return 0;
}