/*
Count the Number of Substrings With Dominant Ones - [Leetcode - 3234(Medium)]
-------------------------------------------------------------------------------
You are given a binary string s.

Return the number of substrings with dominant ones.

A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.

Example 1:

Input: s = "00011"

Output: 5

Explanation:

The substrings with dominant ones are shown in the table below.

i	j	s[i..j]	Number of Zeros	Number of Ones
3	3	1	0	1
4	4	1	0	1
2	3	01	1	1
3	4	11	0	2
2	4	011	1	2

Example 2:

Input: s = "101101"

Output: 16

Explanation:

The substrings with non-dominant ones are shown in the table below.

Since there are 21 substrings total and 5 of them have non-dominant ones, it follows that there are 16 substrings with dominant ones.

i	j	s[i..j]	Number of Zeros	Number of Ones
1	1	0	1	0
4	4	0	1	0
1	4	0110	2	2
0	4	10110	2	3
1	5	01101	2	3


Constraints:

1 <= s.length <= 4 * 104
s consists only of characters '0' and '1'.
*/ 

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int numberOfSubstrings(string s) {
    int n = s.length();

    // Precalculate the prefix sums of zeros and ones
    vector<int> cumCountOne(n, 0);
    cumCountOne[0] = (s[0] == '1') ? 1 : 0;

    for(int i = 1; i < n; i++){
        cumCountOne[i] = cumCountOne[i-1] + (s[i] == '1' ? 1 : 0);
    }

    int result = 0;

    // O(n * n) worst
    // j - i + 1 = l
    // l^2 -------> ~n
    // l = sqrt(n)
    // O(n * sqrt(n)) average --- best case
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            int oneCount = cumCountOne[j] - (i - 1 >= 0 ? cumCountOne[i-1] : 0);
            int zeroCount = (j - i + 1) - oneCount;

            if((zeroCount * zeroCount) > oneCount){
                // SKip j to avoid indices
                int wasteIndices = (zeroCount * zeroCount) - oneCount;
                j += wasteIndices - 1; // -1 because the loop will increment j
            } else if ((zeroCount * zeroCount) == oneCount){
                result += 1;
            } else { // (zeroCount * zeroCount) < oneCount
                //[i....j] is a valid substring, and all substrings starting from i and ending at k (where j <= k < n) will also be valid
                result += 1;

                // Try to see how much j can right untill substring dominant
                int k = sqrt(oneCount) - zeroCount;
                int nextJ = j + k;

                if(nextJ >= n){ // out of bounds
                    result += (n - j - 1); // all remaining substrings are valid
                    break;
                } else {
                    result += k;
                }

                j = nextJ; // move j to the next valid position
            }
        }
    }

    return result;
}

int main() {
    string s = "00011";
    cout << numberOfSubstrings(s) << endl; // Output: 5

    s = "101101";
    cout << numberOfSubstrings(s) << endl; // Output: 16

    return 0;
}