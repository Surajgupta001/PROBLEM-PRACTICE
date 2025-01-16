#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

vector<int> intersection(vector<int>&v1, vector<int>&v2){

    // creating a new ans vector to store common element
    vector<int>ans;

    int ptr1 = 0; // left pointer
    int ptr2 = 0; // right pointer

    // sorting element
    sort(v1.begin(),v1.end()); // sorting 1st vector
    sort(v2.begin(),v2.end()); // sorting 2nd vector

    while(ptr1<v1.size() && ptr2<v2.size()){
        if(v1[ptr1] == v2[ptr2]){
            ans.push_back(v1[ptr1]);
            ptr1++;
            ptr2++;
        }
        else if(v1[ptr1]<v2[ptr2]){
            ptr1++;
        }
        else{
            ptr2++;
        }
    }
    return ans;
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

    vector<int>result = intersection(v1,v2);

    cout<<"Common Element: "<<endl;
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<" ";
    }

    return 0;
}