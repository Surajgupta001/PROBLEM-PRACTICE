/*
Maximum Number of Operations to Move Ones to the End - [Leetcode - 3228(Medium)]
----------------------------------------------------------------------------------
You are given a binary string s.

You can perform the following operation on the string any number of times:

Choose any index i from the string where i + 1 < s.length such that s[i] == '1' and s[i + 1] == '0'.
Move the character s[i] to the right until it reaches the end of the string or another '1'. For example, for s = "010010", if we choose i = 1, the resulting string will be s = "000110".
Return the maximum number of operations that you can perform.

Example 1:

Input: s = "1001101"

Output: 4

Explanation:

We can perform the following operations:

Choose index i = 0. The resulting string is s = "0011101".
Choose index i = 4. The resulting string is s = "0011011".
Choose index i = 3. The resulting string is s = "0010111".
Choose index i = 2. The resulting string is s = "0001111".
Example 2:

Input: s = "00111"

Output: 0

Constraints:

1 <= s.length <= 10^5
s[i] is either '0' or '1'.
 
*/

#include <iostream>
#include <string>
using namespace std;

int maxOperations(string s) {
    int n = s.length();
    int result = 0;
    int i = 0;
    int count1Seen = 0; // count of 1's seen so far

    // NOTE : For maximise => traverse left to right
    // NOTE : For minimise => traverse right to left

    // NOTE : Count number of 1's before that till 0's = number of operations
    // i.e. 110 => 2 operations because two 1's before 0

    // LOGIC :
    // 1. keep counter of 1
    // 2. s[i] == '0' => add count of 1 to result; more 1's before 0 => more operations
    // 3. s[i] == '1' => increment count of 1

    while(i < n){
        if(s[i] == '0'){
            result += count1Seen;
            while(i < n && s[i] == '0'){ // removed till first '1' occurance
                i++;
            }
        }
        else {
            count1Seen++;
            i++;
        }
    }

    return result;
}

int main() {
    string s = "1001101";
    cout << "Maximum number of operations: " << maxOperations(s) << endl; // Output: 4
    return 0;
}