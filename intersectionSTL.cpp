#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
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

    // sorting 2 vectors
    sort(v1.begin(),v1.end()); // sorting 1st vector
    sort(v2.begin(),v2.end()); // sorting 2nd vector

    vector<int>commonElement;

    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(commonElement));

    cout<<"Common Element: ";
    for(int i=0;i<commonElement.size();i++){
        cout<<commonElement[i]<<" ";
    }

    return 0;
}