/*
ADD BINARY - (LEETCODE - 67) - BIT MANUPULATION
Given two binary strings a and b, return their sum as a binary string.

Example 1:

Input: a = "11", b = "1"
Output: "100"

Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
*/
#include <iostream>
#include <string>
using namespace std;

string addBinary(string str1, string str2){
    
    int i = 0; // iterate whole string
    int carry = 0;
    string ans = ""; // Empty string

    while(i<str1.size() || i<str2.size() || carry != 0){
        int x = 0;
        if(i<str1.size() && str1[str1.size()-i-1] == '1'){
            x = 1;
        }

        int y = 0;
        if(i<str2.size() && str2[str2.size()-i-1] == '1'){
            y = 1;
        }
        
        // The "to_string()" function can be used to convert an integer, floating point values, or any number to a string. This function accepts a number(which can be any data type) and returns the number as the desired string.

        ans = to_string((x+y+carry)%2) + ans; 
        carry = (x+y+carry)/2;
        i = i+1;
    }
    return ans;
}
/*
======== Optimised Code ===========
string addBinary(string a, string b) {
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        string ans = "";

        while (i >= 0 || j >= 0 || carry != 0) {
            int x = (i >= 0 && a[i--] == '1') ? 1 : 0;
            int y = (j >= 0 && b[j--] == '1') ? 1 : 0;
            int sum = x + y + carry;
            ans = (sum % 2 == 1) ? "1" + ans : "0" + ans;
            carry = sum / 2;
        }
        return ans;
    }
*/ 
int main(){

    string str1;
    cout<<"Enter a 1st String: ";
    cin>>str1;

    string str2;
    cout<<"Enter a 2nd String: ";
    cin>>str2;

    string result = addBinary(str1, str2);
    cout<<"Addition of Binary Numbers: "<<result<<endl;

    return 0;
}