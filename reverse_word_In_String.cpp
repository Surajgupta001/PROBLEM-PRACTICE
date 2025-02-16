/*
Reverse Words in a String - [Leetcode - 151(Medum)]
===================================================

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.


Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:

Input: s = "hello world"
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:

Input: s = "a good example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string reverseWord(string str){
    // Remove leading and trailing spaces
    while (!str.empty() && str[0] == ' ') str.erase(0, 1);
    while (!str.empty() && str[str.length() - 1] == ' ') str.erase(str.length() - 1, 1);

    string word = ""; // store each word
    string reversed = ""; // store the final reversed string
    for(int i= str.length()-1;i>=0;i--){

        // If we have a space and word is not empty
        if(str[i] == ' ' and !word.empty()){
            reversed += word + " "; // Add the word in reverse order with having space maintaining
            word = ""; // Reset the word variable for the next word
        }
        // If the character is not a space, add it to the front of the current word
        else if(str[i] != ' ') word = str[i] + word; // word in reverse order
    }
    // If there's any remaining word after the loop, add it to the reversed string
    if(!word.empty()) reversed += word;
    return reversed;
}

int main(){
    
    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    cout << reverseWord(str) << endl;

    return 0;
}