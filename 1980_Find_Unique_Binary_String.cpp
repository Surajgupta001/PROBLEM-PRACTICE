/*
Find Unique Binary String - [Leetcode - 1980(Medium)]
---------------------------------------------------------
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

Example 1:

Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.

Example 2:

Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.

Example 3:

Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct. 

Constraints:

n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <bitset>
#include <functional>
using namespace std;

//Approach-1 (Using simple conversion)
//T.C : O(n^2) - Iterating on each string and converting each character to integer
//S.C : O(n) - Using set
string findDifferentBinaryString(vector<string>& nums) {
    unordered_set<int> st;
    
    for(string &num : nums) {
        st.insert(stoi(num, 0, 2));
    }
    
    int n = nums.size();
    
    string result= "";
    
    for(int number = 0; number <= n; number++) {
        if(st.find(number) == st.end()) {
            result = bitset<16>(number).to_string();
            break;
        }
    }
    
    return result.substr(16-n);
}

//Approach-2 (Improving above code)
//We no need to check from 0 to 65536. Only need to check from 0 to n
//T.C : O(n^2) - Iterating on each string and converting each character to integer
//S.C : O(n) - Using set
string findDifferentBinaryString(vector<string>& nums) {
    // Generate all string of length n
    // Recursion + Backtracking
    unordered_set<string> st(nums.begin(), nums.end());
    string result = "";
    
    function<bool(string)> backtracking = [&](string current) {
        if(current.length() == nums.size()) {
            if(st.find(current) == st.end()) {
                result = current;
                return true;
            }
            return false;
        }
        
        current.push_back('0');
        if(backtracking(current)) return true;
        current.pop_back();
        
        current.push_back('1');
        if(backtracking(current)) return true;
        current.pop_back();
        
        return false;
    };

    backtracking("");
    return result;
}

//Approach-3 (By discarding matching characters in each position)
//T.C : O(n)
//S.C : O(1)
string findDifferentBinaryString(vector<string>& nums) {
    string result = "";
    int n = nums.size();
    
    for(int i = 0; i < n; i++) {
        if(nums[i][i] == '0') {
            result.push_back('1');
        } else {
            result.push_back('0');
        }
    }
    
    return result;
}

int main() {
    vector<string> nums = {"00","01"};
    cout << findDifferentBinaryString(nums) << endl; // Output: "11"
    return 0;
}