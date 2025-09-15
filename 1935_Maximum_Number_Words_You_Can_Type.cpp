/*
Maximum Number of Words You Can Type - [Leetcode - 1935(Easy)]
---------------------------------------------------------------
There is a malfunctioning keyboard where some letter keys do not work. All other keys on the keyboard work properly.

Given a string text of words separated by a single space (no leading or trailing spaces) and a string brokenLetters of all distinct letter keys that are broken, return the number of words in text you can fully type using this keyboard.

Example 1:

Input: text = "hello world", brokenLetters = "ad"
Output: 1
Explanation: We cannot type "world" because the 'd' key is broken.

Example 2:

Input: text = "leet code", brokenLetters = "lt"
Output: 1
Explanation: We cannot type "leet" because the 'l' and 't' keys are broken.

Example 3:

Input: text = "leet code", brokenLetters = "e"
Output: 0
Explanation: We cannot type either word because the 'e' key is broken.
 

Constraints:

1 <= text.length <= 104
0 <= brokenLetters.length <= 26
text consists of words separated by a single space without any leading or trailing spaces.
Each word only consists of lowercase English letters.
brokenLetters consists of distinct lowercase English letters.
*/ 

#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

int canBeTypedWords(string text, string brokenLetters) {
    unordered_set<char> brokenSet(brokenLetters.begin(), brokenLetters.end());
    int count = 0;
    string word;
    /* `stringstream` is a class in C++ that is used for parsing input strings. In the given code
    snippet, `stringstream ss(text)` is creating a stringstream object `ss` initialized with the
    input string `text`. This allows the input string `text` to be treated as a stream of characters
    that can be easily processed using stream extraction operators like `>>`. In this case, `ss >>
    word` is used to extract individual words from the input string `text` for further processing. */
    stringstream ss(text);
    while(ss /* The `>>` operator in C++ is known as the stream extraction operator. It is used to
    extract data from a stream, such as input from the standard input (keyboard) or from a
    stringstream. */
    >> word){
        bool canType = true;
        for(auto &ch : word){
            if(brokenSet.count(ch)){
                canType = false;
                break;
            }
        }
        if(canType) count++;
    }
    return count;
}

int main() {
    string text = "hello world";
    string brokenLetters = "ad";
    cout << canBeTypedWords(text, brokenLetters) << endl; // Output: 1
    return 0;
}