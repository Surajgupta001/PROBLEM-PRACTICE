/*
Vowel Spellchecker - [Leetcode - 966(Medium)]
----------------------------------------------
Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.

For a given query word, the spell checker handles two categories of spelling mistakes:

Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
In addition, the spell checker operates under the following precedence rules:

When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
When the query matches a word up to capitlization, you should return the first such match in the wordlist.
When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
If the query has no matches in the wordlist, you should return the empty string.
Given some queries, return a list of words answer, where answer[i] is the correct word for query = queries[i].

Example 1:

Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]

Example 2:

Input: wordlist = ["yellow"], queries = ["YellOw"]
Output: ["yellow"]

Constraints:

1 <= wordlist.length, queries.length <= 5000
1 <= wordlist[i].length, queries[i].length <= 7
wordlist[i] and queries[i] consist only of only English letters.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_set<string> exactsets;
unordered_map<string, string> casemaps;
unordered_map<string, string> vowelmaps;

// Converting entire string to lowercase
string toLowerCase(string &str){
    string lowerCase = str;
    for(auto &ch : lowerCase){
        ch = tolower(ch);
    }
    return lowerCase;
}

// Replacing all vowels with '*'
string toReplaceVowel(string &str){
    string vowelCase = str;
    for(auto &ch : vowelCase){
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
            ch = '*';
        }
    }
    return vowelCase;
}

// Check for match in exactsets, casemaps and vowelmaps
string checkForMatch(string &query){
    // Exact match check
    if(exactsets.find(query) != exactsets.end()){
        return query;
    }

    // Case error check
    string lowerCase = toLowerCase(query);
    if(casemaps.find(lowerCase) != casemaps.end()){
        return casemaps[lowerCase];
    }
    
    // Vowel error check
    string vowelCase = toReplaceVowel(lowerCase);
    if(vowelmaps.find(vowelCase) != vowelmaps.end()){
        return vowelmaps[vowelCase];
    }
    
    return "";
}

vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
    exactsets.clear(); // Clear exact match set
    casemaps.clear(); // Clear case error map
    vowelmaps.clear(); // Clear vowel error map
    
    for(auto word : wordlist){
        // Inserting word in exact match set
        exactsets.insert(word);

        // Inserting word in case error map
        string lowerCase = toLowerCase(word);
        // If not already present, insert the lowercase version of the word
        if(casemaps.find(lowerCase) == casemaps.end()){
            casemaps[lowerCase] = word;
        }

        // Inserting word in vowel error map
        string vowelCase = toReplaceVowel(lowerCase);
        // If not already present, insert the vowel replaced version of the word
        if(vowelmaps.find(vowelCase) == vowelmaps.end()){
            vowelmaps[vowelCase] = word;
        }
    }

    // For each query, check for match and store the result
    vector<string> result;
    // Iterate through each query
    for(auto query : queries){
        // Check for match and store the result
        result.push_back(checkForMatch(query));
    }

    return result;
}

int main() {

    vector<string> wordlist = {"KiTe","kite","hare","Hare"};
    vector<string> queries = {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"};
    
    vector<string> result = spellchecker(wordlist, queries);
    
    for(string word : result) {
        cout << word << " ";
    }
    cout << endl;

}