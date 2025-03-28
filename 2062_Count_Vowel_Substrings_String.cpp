/*
Count Vowel Substrings of a String - [Leetcode - 2062(Easy)]
=============================================================
A substring is a contiguous (non-empty) sequence of characters within a string.

A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.

Given a string word, return the number of vowel substrings in word.

Example 1:

Input: word = "aeiouu"
Output: 2
Explanation: The vowel substrings of word are as follows (underlined):
- "aeiouu"
- "aeiouu"

Example 2:

Input: word = "unicornarihan"
Output: 0
Explanation: Not all 5 vowels are present, so there are no vowel substrings.

Example 3:

Input: word = "cuaieuouac"
Output: 7
Explanation: The vowel substrings of word are as follows (underlined):
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
 

Constraints:

1 <= word.length <= 100
word consists of lowercase English letters only.
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// int countVowelSubString(string word){
//     int n = word.length();
//     int count = 0;
//     unordered_set<char>vowels = {'a', 'e', 'i', 'o', 'u'};

//     for(int i=0; i<n; i++){
//         unordered_set<char>currentVowels;
//         for(int j=i; j<n; j++){
//             if(vowels.count(word[j])){
//                 currentVowels.insert(word[j]);
//                 if(currentVowels.size() == 5){
//                     count++;
//                 }
//             } else {
//                 break;
//             }
//         }
//     }
//     return count;
// }

// Another Optimised Approch
int countVowelSubString(string word){
    int n = word.length();
    int count = 0;
    unordered_set<char>vowels = {'a', 'e', 'i', 'o', 'u'};
    vector<int>vowelCount(5,0); // frequency array for vowels
    vector<char> vowelMap = {'a', 'e', 'i', 'o', 'u'};

    for(int i=0; i<n; i++){
        if(vowels.count(word[i])){
            for(int k=0; k<5; k++){
                if(word[i] == vowelMap[k]){
                    vowelCount[k]++; // increment frequency count
                    break;
                }
            }
            int j = i;
            while(j < n && vowels.count(word[j])){
                for(int k=0; k<5; k++){
                    if(word[j] == vowelMap[k]){
                        vowelCount[k]++; // increment frequency count
                        break;
                    }
                }
                bool allVowelsPresent = true;
                for(int k=0; k<5; k++){
                    if(vowelCount[k] == 0){
                        allVowelsPresent = false;
                        break;
                    }
                }
                if(allVowelsPresent){
                    count++;
                }
                j++;
            }
            // reset frequency count for next window
            for(int k=0; k<5; k++){
                vowelCount[k] = 0;
            }
        }
    }
    return count;
}

int main(){
    string word = "aeiouu";
    cout << countVowelSubString(word) << endl;
    return 0;
}