#include <iostream>
#include <vector>
using namespace std;

int linearSearch(vector<int>v, int k){
    
    int ans = -1;

    for(int i=0;i<v.size();i++){
        if(v[i] == k){
            ans = i; // storing index
        }
    }
    return ans;
}
int main(){

    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int>v;
    while(n--){
        int x;
        cin>>x;
        v.push_back(x);
    }

    int k;
    cout<<"Enter target element: ";
    cin>>k;

    int result = linearSearch(v,k);

    if(linearSearch){
        cout<<"Indexes: "<<result<<endl;
    }
    else{
        cout<<"Not found";
    }

    return 0;
}