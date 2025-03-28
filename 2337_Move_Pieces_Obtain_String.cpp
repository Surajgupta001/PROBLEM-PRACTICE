/*
Move Pieces to Obtain a String - [Leetcode - 2337(Medium)]
============================================================

You are given two strings start and target, both of length n. Each string consists only of the characters 'L', 'R', and '_' where:

The characters 'L' and 'R' represent pieces, where a piece 'L' can move to the left only if there is a blank space directly to its left, and a piece 'R' can move to the right only if there is a blank space directly to its right.
The character '_' represents a blank space that can be occupied by any of the 'L' or 'R' pieces.
Return true if it is possible to obtain the string target by moving the pieces of the string start any number of times. Otherwise, return false.

Example 1:

Input: start = "_L__R__R_", target = "L______RR"
Output: true
Explanation: We can obtain the string target from start by doing the following moves:
- Move the first piece one step to the left, start becomes equal to "L___R__R_".
- Move the last piece one step to the right, start becomes equal to "L___R___R".
- Move the second piece three steps to the right, start becomes equal to "L______RR".
Since it is possible to get the string target from start, we return true.

Example 2:

Input: start = "R_L_", target = "__LR"
Output: false
Explanation: The 'R' piece in the string start can move one step to the right to obtain "_RL_".
After that, no pieces can move anymore, so it is impossible to obtain the string target from start.

Example 3:

Input: start = "_R", target = "R_"
Output: false
Explanation: The piece in the string start can move only to the right, so it is impossible to obtain the string target from start.
*/ 


#include <iostream>
#include <string>
using namespace std;

bool canChange(string start, string target){
    if(start.size() != target.size()) return false;

    // Count the number of 'L' and 'R' pieces in the start and target string
    int ST = 0; // Start Left
    int SR = 0; // Start Right
    int TL = 0; // Target Left
    int TR = 0; // Target Right
    for(int i = 0; i < start.size(); i++){
        if(start[i] == 'L') ST++;
        else if(start[i] == 'R') SR++;
        if(target[i] == 'L') TL++;
        else if(target[i] == 'R') TR++;
    }
    // If the number of 'L' or 'R' pieces is different, return false
    if(ST != TL || SR != TR) return false;
    
    int i = 0; // start pointer
    int j = 0; // target pointer

    while(i < start.size() and j < target.size()){
        // If the current character match, move both pointer
        if(start[i] == target[j]){
            i++;
            j++;
        }
        // If the current character in the start string is '_', move the pointer
        else if(start[i] == '_'){
            i++;
        }
        // If the current character in the target string is '_', move the pointer
        else if(target[j] == '_'){
            j++;
        }
        else{
            // If the current characters do not match and are not '_', return false
            return false;
        }
    }
    // If all character have been matched, return true
    return true;
}

int main(){

    string str;
    cout<<"Enter a string: ";
    cin>>str;

    string target;
    cout<<"Enter a target string: ";
    cin>>target;

    cout<<boolalpha<<canChange(str, target)<<endl;

    return 0;
}