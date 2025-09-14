/*
You a given a integer n. Your task is to find the sum of the digits of n until the sum becomes a single digit.

Example 1:
Input: n = 9875
Output: 2

Explanation: 
9 + 8 + 7 + 5 = 29
2 + 9 = 11
1 + 1 = 2
*/

#include <iostream>
#include <string>
using namespace std;

int reduceToSingleDigit(int nums){
    int sum = 0;
    while(nums > 0){
        sum += nums % 10;
        nums /= 10; 
    }
    if(sum > 9){
        return reduceToSingleDigit(sum);
    }
    return sum;
}

int reduceToSingleDigit(int nums){
    string str = to_string(nums);
    while(str.length() > 1){
        int sum = 0;
        for(int i = 0; i < str.length(); i++){
            sum += (str[i] - '0'); // In C++, characters are stored as their ASCII values.
        }
        str = to_string(sum);
    }
    return str[0] - '0'; // str.length() == 1, so exit loop. Return str[0] - '0' → '2' - '0' = 2
}

int main() {

    int n = 9875;
    cout << reduceToSingleDigit(n) << endl;

}