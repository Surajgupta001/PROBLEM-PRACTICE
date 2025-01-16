/*
ADDING ONE TO NUMBER REPRESENTED AS ARRAY OF DIGITS(LEETCODE)

Given a non-negative number represented as an array of digits, add 1 to the number ( increment the number represented by the digits ). The digits are stored such that the most significant digit is the first element of the array.

Examples-1: 

Input 1: [1, 2, 4]
Output : [1, 2, 5]

Example-2:

Input 2: [9, 9, 9]
Output : [1, 0, 0, 0]
*/
#include <iostream>
#include <vector>is
using namespace std;

vector<int> digitarrayPlusOne(vector<int>&digits){
    
    int carry = 1;

    for(int i=digits.size()-1;i>=0;i--){
        int sum = digits[i]+carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    if(carry > 0){
        digits.insert(digits.begin(),carry);
    }
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

    vector<int>result = digitarrayPlusOne(v);
    cout<<"Digit Array Plus One: ";
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<" ";
    }

    return 0;
}
