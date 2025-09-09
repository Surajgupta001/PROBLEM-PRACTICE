/*
Convert Integer to the Sum of Two No-Zero Integers - [Leetcode - 1317(Easy)]
------------------------------------------------------------------------------
No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.

Given an integer n, return a list of two integers [a, b] where:

a and b are No-Zero integers.
a + b = n
The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.

 

Example 1:

Input: n = 2
Output: [1,1]
Explanation: Let a = 1 and b = 1.
Both a and b are no-zero integers, and a + b = 2 = n.
Example 2:

Input: n = 11
Output: [2,9]
Explanation: Let a = 2 and b = 9.
Both a and b are no-zero integers, and a + b = 11 = n.
Note that there are other valid answers as [8, 3] that can be accepted.
 

Constraints:

2 <= n <= 104
 

*/ 

#include <iostream>
#include <vector>
using namespace std;

//      n 
//     / \
      a   n-a

//  let say n = 11
//  a = 1, b = 11-1=10 => X -> not possible
//  a = 2, b = 11-2=9 => X -> possible
//  a = 3, b = 11-3=8 => X -> possible
//  a = 4, b = 11-4=7 => X -> possible
//  a = 5, b = 11-5=6 => X -> possible
//  a = 6, b = 11-6=5 => X -> possible
//  a = 7, b = 11-7=4 => X -> possible
//  a = 8, b = 11-8=3 => X -> possible
//  a = 9, b = 11-9=2 => X -> possible
//  a = 10, b = 11-10=1 => X -> not possible

/*
======================== NPOS ========================
In C++ STL, npos is a constant static member of string classes (like std::string and std::wstring).
It represents a value that means "not found" when searching within a string.

Usage:
When you use functions like find(), if the substring or character is not found, the function returns std::string::npos.

Example:
std::string s = "hello";
if (s.find('z') == std::string::npos) {
    // 'z' was not found in the string
}

Value:
npos is usually defined as the largest possible value for size_t (typically -1 cast to size_t).
*/ 

// Using string STL
// T.C = O(n * log(n)) - log(n) for checking each number
vector<int> getNoZeroIntegers(int n) {
    for(int a=1; a<=n-1; a++){ // iterate through all possible values of a
        int b = n-a; // calculate b
        if(to_string(a).find('0') == string::npos && to_string(b).find('0') == string::npos) { // check if both a and b are no-zero integers
            return {a, b}; // return the valid pair
        }
    }
    return {};
}

bool check(int num){
    while(num){
        if(num%10 == 0)
            return false;
        num = num/10;
    }
    return true;
}
// T.C = O(n * log(n)) - log(n) for checking each number
vector<int> getNoZeroIntegers(int n) {
    for(int a=1; a<=n-1; a++){
        int b = n-a;

        if(check(a) && check(b)){
            return {a, b};
        }
    }
    return {};
}

// Better Approach - T.C = (log(n))
vector<int> getNoZeroIntegers(int n) {
    int a = n;
    int b = 0;
    int placedValue = 1; // 10^0 = 1, 10^1 = 10, 10^2 = 100

    // a+b == n
    while(n > 1){
        int take = 1;

        if(n % 10 == 1){
            take = 2;
        }

        a = a - take * placedValue;
        b = b + take * placedValue;

        n = (n-take)/10; // moving to next digit
        placedValue = placedValue * 10; // moving to next place value
    }
    return {a, b};
}

int main() {
    int n = 11;
    vector<int> result = getNoZeroIntegers(n);
    cout << "[" << result[0] << "," << result[1] << "]" << endl;
    return 0;
}