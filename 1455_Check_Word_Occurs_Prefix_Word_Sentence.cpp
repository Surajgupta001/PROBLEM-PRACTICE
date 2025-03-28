/*
Check If a Word Occurs As a Prefix of Any Word in a Sentence - [Leetcode - 1455(Easy)]
============================================================================================

Given a sentence that consists of some words separated by a single space, and a searchWord, check if searchWord is a prefix of any word in sentence.

Return the index of the word in sentence (1-indexed) where searchWord is a prefix of this word. If searchWord is a prefix of more than one word, return the index of the first word (minimum index). If there is no such word return -1.

A prefix of a string s is any leading contiguous substring of s.

Example 1:

Input: sentence = "i love eating burger", searchWord = "burg"
Output: 4
Explanation: "burg" is prefix of "burger" which is the 4th word in the sentence.
Example 2:

Input: sentence = "this problem is an easy problem", searchWord = "pro"
Output: 2
Explanation: "pro" is prefix of "problem" which is the 2nd and the 6th word in the sentence, but we return 2 as it's the minimal index.
Example 3:

Input: sentence = "i am tired", searchWord = "you"
Output: -1
Explanation: "you" is not a prefix of any word in the sentence.
*/ 

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int isPrefixOfWord(string sentence, string searchWord){
    istringstream iss(sentence);
    string word; // create a empty word
    int idx = 1;
    while(iss >> word){
        // The >> operator is used to read from the stream. It reads until it encounters a whitespace character (such as a space, tab, or newline).
        if(word.find(searchWord) == 0) return idx;
        idx++;
    }
    return -1;
}
/*
Q. What is istringstream? =======
== > istringstream is a class in C++ that allows you to read from a string as if it were a stream of input. It is a part of the C++ Standard Library and is used to parse strings into individual words or tokens.

Q. How does istringstream split the string into words? ===
==> istringstream splits the string into words based on whitespace characters. By default, it uses the following whitespace characters:
--> Space ( )
--> Tab (\t)
--> Newline (\n)
--> Vertical tab (\v)
--> Form feed (\f)
*/ 
int main(){
    string str1;
    cout<<"Enter a sentence: ";
    getline(cin, str1);

    string str2;
    cout<<"Enter a search word: ";
    cin>>str2;

    cout<<"Index of the word in sentence is: "<<isPrefixOfWord(str1, str2);
    
    return 0;
}