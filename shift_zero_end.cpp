#include <iostream>
#include <vector>
using namespace std;

void movesZerosEnd(vector<int>&v){

    int i = 0; // left pointer
    int j = 0; // right pointer

    for(int i=0;i<v.size();i++){
        if(v[i] != 0){
            swap(v[i],v[j]);
            j++;
        }
    }
}
int main(){
    
    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    cout<<"Enter all the element of vectors: ";
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    movesZerosEnd(v);
    cout<<"Move Zero End: ";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }

    return 0;
}