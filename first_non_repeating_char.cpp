/*
First non-repeating character in a stream

Example 1:

Input: str = "aabc"
Output: "a#bb"

Example 2:

Input 2: "zz"
Output: "z#"
*/
#include <iostream>
#include <queue>
#include <string>
using namespace std;

string firstNonRepeating(string str){

    // Step 1: Initialize Frequency Array(store the frequency of each character) and Queue
    int freq[26] = {0};
    queue<char> qu;
    string ans = "";

    // Step 2: Traverse the string and update the frequency array and queue
    for (int i=0; i<str.length(); i++){

        freq[str[i] - 'a']++; // Increment the frequency of the current the 'freq' array
        qu.push(str[i]);      // push the current character into queue 'qu'.

        // Step 3: Remove Repeating character from the queue
        // While the queue is not empty and the frequency of the front character is greater than 1, pop the front character from the queue.
        while (!qu.empty() && freq[qu.front() - 'a'] > 1) qu.pop();

        // Step 4: Get the First Non-Repeating Character
        if(qu.empty()) ans += "#";
        else ans += qu.front();
    }
    // Step 5: Return ans String
    return ans;
}

int main(){

    string str;
    cout<<"Enter a string: ";
    cin>>str;

    cout<<"First Non-Repeating Character: "<<firstNonRepeating(str)<<endl;

    return 0;
}