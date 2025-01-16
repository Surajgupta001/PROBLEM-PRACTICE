#include <iostream>
#include <vector>
using namespace std;

vector<int>digitArrayPlusOne(vector<int>&digits){
    for(int i=digits.size()-1;i>=0;i--){
        if(digits[i] == 9){
            digits[i] = 0;
        }
        else{
            digits[i] += 1;
            return digits;
        }
    }
    digits.insert(digits.begin(),1);
    return digits;
}
int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    cout<<"Enter all the elements of vectors: ";
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    vector<int>result = digitArrayPlusOne(v);
    cout<<"Digit Array Plus One: ";
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<" ";
    }

    return 0;
}