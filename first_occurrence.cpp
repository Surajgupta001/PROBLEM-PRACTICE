/*
FIND THE INDEX OF THE FIRST OCCURRENCE IN A STRING - (LEETCODE-28).
=====================================================
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.

Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 
Constraints:
* 1 <= haystack.length, needle.length <= 104
* haystack and needle consist of only lowercase English characters.

*/
#include <iostream>
#include <string>
using namespace std;

int firstOccurrence(string haystack, string needle){

    /*
    * TIME : O(haystack.size().needle.size())
    * SPACE : O(needle.size())
    */ 

    if (haystack.size() < needle.size()) return -1;

    for(int i=0;i<=haystack.size()-needle.size();i++){
        if(haystack.substr(i,needle.size()) == needle){
            return i;
        }
    }
    return -1;
}
int main(){
    
    string haystack = "sadbutsad";
    string needle = "sad";
    int index = firstOccurrence(haystack, needle);
    cout << "Index of first occurrence: " << index << endl;
    return 0;
}



#include <iostream>
#include <string>
using namespace std;

int firstOccurrence(string haystack, string needle){

    if(haystack.size() < needle.size()) return -1;

    for(int i=0;i<=(haystack.size() - needle.size());i++){
        if(haystack[i] == needle[0]){
            int j = 0;
            while(j < needle.size() && haystack[i+j] == needle[j]){
                j++;
            }
            if(j == needle.size()) return i;
        }
    }
    return -1;
}
int main(){
    
    string haystack = "sadbutsad";
    string needle = "sad";
    int index = firstOccurrence(haystack, needle);
    cout << "Index of first occurrence: " << index << endl;
    return 0;
}
