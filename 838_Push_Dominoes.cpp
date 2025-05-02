/*
Push Dominoes - [Leetcode - 838(Medium)]
========================================
There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the left or to the right.

After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.

For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.

You are given a string dominoes representing the initial state where:

dominoes[i] = 'L', if the ith domino has been pushed to the left,
dominoes[i] = 'R', if the ith domino has been pushed to the right, and
dominoes[i] = '.', if the ith domino has not been pushed.
Return a string representing the final state.

Example 1:

Input: dominoes = "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.

Example 2:

Input: dominoes = ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."
 

Constraints:

n == dominoes.length
1 <= n <= 105
dominoes[i] is either 'L', 'R', or '.'.
*/ 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string pushDominoes(string dominoes) {
    int n = dominoes.length();
    
    vector<int> rightClosestLeft(n);
    vector<int> leftClosestRight(n);
    
    // Moving right to left to find rightClosestLeft 
    for(int i = n-1; i>=0; i--) {
        if(dominoes[i] == 'L'){
            rightClosestLeft[i] = i; //L starts from me
        }
        else if(dominoes[i] == '.'){
            rightClosestLeft[i] = i < n-1 ? rightClosestLeft[i+1] : -1;
        }
        else{
            rightClosestLeft[i] = -1;
        }
    }
    
    // Moving left to right to find leftClosestRight
    for(int i = 0; i<n; i++) {
        if(dominoes[i] == 'R'){
            leftClosestRight[i] = i; //R starts from me
        }
        else if(dominoes[i] == '.'){
            leftClosestRight[i] = i > 0 ? leftClosestRight[i-1] : -1;
        }
        else{
            leftClosestRight[i] = -1;
        }
    }
    
    string ans(n, ' ');
    
    for(int i = 0; i<n; i++) {
        
        int distRightLeft = abs(i - rightClosestLeft[i]); //distance from 'R' towards my left direction
        int distLeftRight  = abs(i - leftClosestRight[i]);  //distance from 'L' towards my right direction
        
        if(rightClosestLeft[i] == leftClosestRight[i]){
            ans[i] = '.';
        }
        else if(rightClosestLeft[i] == -1){  //No force from right direction towards left, so move R
            ans[i] = 'R';
        }
        else if(leftClosestRight[i] == -1){   //No force from left direction towards right, so move L
            ans[i] = 'L';
        }
        else if(distLeftRight == distRightLeft){ //Equal force from left and right
            ans[i] = '.';
        }
        else{
            ans[i] = distRightLeft < distLeftRight ? 'L': 'R'; //which ever force is greater (either from left by 'R' or from right by 'L') 
        }
    }

    return ans;
}

int main(){
    
    string dominoes = ".L.R...LR..L.";
    string result = pushDominoes(dominoes);
    
    cout << result << endl;
    
    return 0;
}