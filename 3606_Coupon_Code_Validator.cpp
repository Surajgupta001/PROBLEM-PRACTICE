/*
Coupon Code Validator - [Leetcode - 3542(Easy)]
-------------------------------------------------
You are given three arrays of length n that describe the properties of n coupons: code, businessLine, and isActive. The ith coupon has:

=> code[i]: a string representing the coupon identifier.
=> businessLine[i]: a string denoting the business category of the coupon.
=> isActive[i]: a boolean indicating whether the coupon is currently active.
A coupon is considered valid if all of the following conditions hold:

1. code[i] is non-empty and consists only of alphanumeric characters (a-z, A-Z, 0-9) and underscores (_).
2. businessLine[i] is one of the following four categories: "electronics", "grocery", "pharmacy", "restaurant".
3. isActive[i] is true.

Return an array of the codes of all valid coupons, sorted first by their businessLine in the order: "electronics", "grocery", "pharmacy", "restaurant", and then by code in lexicographical (ascending) order within each category.

Example 1:

Input: code = ["SAVE20","","PHARMA5","SAVE@20"], businessLine = ["restaurant","grocery","pharmacy","restaurant"], isActive = [true,true,true,true]

Output: ["PHARMA5","SAVE20"]

Explanation:

First coupon is valid.
Second coupon has empty code (invalid).
Third coupon is valid.
Fourth coupon has special character @ (invalid).

Example 2:

Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], businessLine = ["grocery","electronics","invalid"], isActive = [false,true,true]

Output: ["ELECTRONICS_50"]

Explanation:

First coupon is inactive (invalid).
Second coupon is valid.
Third coupon has invalid business line (invalid).

Constraints:

n == code.length == businessLine.length == isActive.length
1 <= n <= 100
0 <= code[i].length, businessLine[i].length <= 100
code[i] and businessLine[i] consist of printable ASCII characters.
isActive[i] is either true or false.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;


bool checkValidCode(string &code) {
    if(code.empty()) return false;
    
    for(char &ch : code) {
        if(!isalnum(ch) && ch != '_') {
            return false;
        }
    }

    return true;
}

vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
    
    unordered_map<string, int> mp = {
        {"electronics", 0},
        {"grocery", 1},
        {"pharmacy", 2},
        {"restaurant", 3}
    };

    vector<pair<int, string>> temp; //{businessLineIntegerValue, code}
    
    for (int i = 0; i < code.size(); i++) {
        if (isActive[i] && mp.count(businessLine[i]) && checkValidCode(code[i])) {
            temp.push_back({mp[businessLine[i]], code[i]});
        }
    }
    
    sort(begin(temp), end(temp));
    
    vector<string> result;
    
    for(auto &it : temp) {
        result.push_back(it.second);
    }
    
    return result;
}

int main() {
    vector<string> code = {"SAVE20","","PHARMA5","SAVE@20"};
    vector<string> businessLine = {"restaurant","grocery","pharmacy","restaurant"};
    vector<bool> isActive = {true,true,true,true};

    vector<string> validCoupons = validateCoupons(code, businessLine, isActive);

    for (const string& coupon : validCoupons) {
        cout << coupon << " ";
    }
    cout << endl;

    return 0;
}