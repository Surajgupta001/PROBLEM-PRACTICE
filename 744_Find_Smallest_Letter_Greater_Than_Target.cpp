/*
Find Smallest Letter Greater Than Target - [Leetcode - 744(Easy)]
-------------------------------------------------------------------
You are given an array of characters letters that is sorted in non-decreasing order, and a character target. There are at least two different characters in letters.

Return the smallest character in letters that is lexicographically greater than target. If such a character does not exist, return the first character in letters.

Example 1:

Input: letters = ["c","f","j"], target = "a"
Output: "c"
Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.

Example 2:

Input: letters = ["c","f","j"], target = "c"
Output: "f"
Explanation: The smallest character that is lexicographically greater than 'c' in letters is 'f'.

Example 3:

Input: letters = ["x","x","y","y"], target = "z"
Output: "x"
Explanation: There are no characters in letters that is lexicographically greater than 'z' so we return letters[0].
 
Constraints:

2 <= letters.length <= 10^4
letters[i] is a lowercase English letter.
letters is sorted in non-decreasing order.
letters contains at least two different characters.
target is a lowercase English letter.
*/  

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char nextGreatestLetter(vector<char>& letters, char target) {
    int n = letters.size();
    
    for(int i=0; i<n; i++){
        if(letters[i] > target){
            return letters[i];
        }
    }
    
    return letters[0];
}

// Custom Binary Search Approach
char nextGreatestLetter(vector<char>& letters, char target) {
    int n = letters.size();
    int low = 0;
    int high = n - 1;
    
    while(low <= high){
        int mid = low + (high - low) / 2;
        
        if(letters[mid] <= target){
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    
    return letters[low % n];
}

// Use Upper Bound or Lower Bound
char nextGreatestLetter(vector<char>& letters, char target) {
    int n = letters.size();
    
    auto itr = upper_bound(letters.begin(), letters.end(), target);
    
    if(itr == letters.end()){
        return letters[0];
    }
    else {
        return *itr;
    }
}

int main() {
    vector<char> letters = {'c', 'f', 'j'};
    char target = 'a';

    char result = nextGreatestLetter(letters, target);
    cout << "The smallest letter greater than " << target << " is: " << result << endl;

    return 0;
}