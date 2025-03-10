/*
Plus One - [Leetcode - 66(Easy)]
+=====================================+
You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.


Example 1:

Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].

Example 2:

Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].

Example 3:

Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9.
Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].
 

Constraints:

1 <= digits.length <= 100
0 <= digits[i] <= 9
digits does not contain any leading 0's.
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> digitarrayPlusOne(vector<int>& digits){
    
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
