/*
check whether given string is palindrome or not.

INPUT: "abba"
OUTPUT: YES

INPUT: "abc"
OUTPUT: NO.

* Time: O(string.size())
* Space: O(1)
*/ 
#include <iostream>
#include <string>
using namespace std;

void checkPalidrome(string str){

    int ptr1 = 0; // move ptr1 to the righ
    int ptr2 = str.size()-1; // move ptr2 to the left

    bool isPalindrome = true;
    while(ptr1 < ptr2){
        if(str[ptr1] != str[ptr2]){
            isPalindrome = false;
            break;
        }
        ptr1++;
        ptr2--;
    }
    if(isPalindrome){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}
int main(){

    string str;
    cout<<"Enter a string: ";
    cin>>str;

    checkPalidrome(str);

    return 0;
}