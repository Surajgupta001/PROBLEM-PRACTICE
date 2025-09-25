/*
Compare Version Numbers - [Leetcode - 165(Medium)]
----------------------------------------------------
Given two version strings, version1 and version2, compare them. A version string consists of revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading zeros.

To compare version strings, compare their revision values in left-to-right order. If one of the version strings has fewer revisions, treat the missing revision values as 0.

Return the following:

If version1 < version2, return -1.
If version1 > version2, return 1.
Otherwise, return 0.
 

Example 1:

Input: version1 = "1.2", version2 = "1.10"

Output: -1

Explanation:

version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.

Example 2:

Input: version1 = "1.01", version2 = "1.001"

Output: 0

Explanation:

Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 3:

Input: version1 = "1.0", version2 = "1.0.0.0"

Output: 0

Explanation:

version1 has less revisions, which means every missing revision are treated as "0".

Constraints:

1 <= version1.length, version2.length <= 500
version1 and version2 only contain digits and '.'.
version1 and version2 are valid version numbers.
All the given revisions in version1 and version2 can be stored in a 32-bit integer.

*/ 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Approach - 1: 2 Pointer Approach
int compareVersion(string version1, string version2) {
    int n1 = version1.size();
    int n2 = version2.size();
    int i = 0, j = 0;

    while(i < n1 || j < n2){
        long num1 = 0;
        long num2 = 0;

        // Extract number from version1
        while(i < n1 && version1[i] != '.'){
            num1 = num1 * 10 + (version1[i] - '0');
            i++;
        }

        // Extract number from version2
        while(j < n2 && version2[j] != '.'){
            num2 = num2 * 10 + (version2[j] - '0');
            j++;
        }

        if(num1 < num2) return -1;
        else if(num1 > num2) return 1;

        i++; // Skip the dot
        j++; // Skip the dot
    }

    return 0; // Both versions are equal
}

// Approach - 2: stringstream using token
// Helper function to split version string into tokens
vector<int> getTokens(string version) {
    vector<int> tokens;
    stringstream ss(version);
    string token;

    while(getline(ss, token, '.')){
        tokens.push_back(stoi(token)); // Convert token to integer and add to tokens vector
    }

    return tokens;
}

int compareVersion(string version1, string version2) {
    vector<int> v1 = getTokens(version1);
    vector<int> v2 = getTokens(version2);

    int m = v1.size();
    int n = v2.size();
    int i = 0;

    while(i < m or i < n){
        int a = (i < m) ? v1[i] : 0;
        int b = (i < n) ? v2[i] : 0;

        if(a < b) return -1;
        else if(a > b) return 1;

        i++;
    }
    return 0; // Both versions are equal
}

int main(){
    string version1 = "1.01";
    string version2 = "1.001";
    cout << compareVersion(version1, version2) << endl; // Output: 0
    return 0;
}