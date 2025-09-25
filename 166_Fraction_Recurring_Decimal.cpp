/*
Fraction to Recurring Decimal - [Leetcode - 166(Medium)]
------------------------------------------------------------
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return any of them.

It is guaranteed that the length of the answer string is less than 104 for all the given inputs.

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"

Example 2:

Input: numerator = 2, denominator = 1
Output: "2"

Example 3:

Input: numerator = 4, denominator = 333
Output: "0.(012)"
 
Constraints:

-2^31 <= numerator, denominator <= 2^31 - 1
denominator != 0
*/ 

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

string fractionToDecimal(int numerator, int denominator) {
    if(numerator == 0) return "0"; // If numerator is 0, the result is always 0

    string result = "";

    if((long long)numerator * (long long)denominator < 0) { // If either numerator or denominator is negative (but not both)
        result += "-";
    }

    long long absNumerator = labs(numerator);
    long long absDenominator = labs(denominator);

    long long integerDiv = absNumerator / absDenominator; // Integer part of the fraction

    result += to_string(integerDiv);

    long long remain = absNumerator % absDenominator; // Remainder after integer division

    if(remain == 0) { // If there is no remainder, return the result
        return result;
    }

    result += "."; // Decimal point

    unordered_map<int, int> remainMap; // Map to store the position of each remainder

    while(remain != 0){
        if(remainMap.find(remain) != remainMap.end()){ // If the remainder has been seen before, we have a repeating decimal
            result.insert(remainMap[remain], "("); // Insert '(' at the position where this remainder was first seen
            result += ")"; // Append ')' at the end
            break;
        }
        remainMap[remain] = result.size(); // Store the position of this remainder
        remain *= 10; // Multiply remainder by 10 to get the next digit
        int digit = remain / absDenominator; // Next digit in the decimal part
        result += to_string(digit); // Append the next digit to the result
        remain %= absDenominator; // Update the remainder
    }
    return result;
}

int main(){
    int numerator = 4;
    int denominator = 333;
    string result = fractionToDecimal(numerator, denominator);
    cout << result << endl; // Output: "0.(012)"
    return 0;
}