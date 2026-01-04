/*
Four Divisors - [Leetcode - 1390(Medium)]
---------------------------------------------
Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.

Example 1:

Input: nums = [21,4,7]
Output: 32
Explanation: 
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.

Example 2:

Input: nums = [21,21]
Output: 64

Example 3:

Input: nums = [1,2,3,4,5]
Output: 0
 
Constraints:

1 <= nums.length <= 10^4
1 <= nums[i] <= 10^5
*/ 

#include <iostream>
#include <vector>
using namespace std;

int findSumDivisor(int num) {
    int divisor = 0; // count of divisors
    int sum = 0;    // sum of divisors

    for(int fact = 1; fact * fact <= num; fact++){
        if(num % fact == 0){
            int other = num / fact;

            if(other == fact){ // perfect square number ka case hai yeh
                divisor += 1;
                sum += fact;
            } else {
                divisor += 2;
                sum += (fact + other);

            }
        }

        if(divisor > 4) return 0; // early exit if more than 4 divisors
    }
    return (divisor == 4) ? sum : 0;
}

int sumFourDivisors(vector<int>& nums) {
    int result = 0;
    
    for(int &num : nums){
        result += findSumDivisor(num);
    }

    return result;
}

int main() {
    vector<int> nums = {21, 4, 7};
    
    cout << sumFourDivisors(nums) << endl; // Output: 32
    
    return 0;
}