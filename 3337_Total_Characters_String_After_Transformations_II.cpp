/*
3337. Total Characters in String After Transformations II - [Leetcode - 3337(Hard)]
-------------------------------------------------------------------------------------
You are given a string s consisting of lowercase English letters, an integer t representing the number of transformations to perform, and an array nums of size 26. In one transformation, every character in s is replaced according to the following rules:

Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet. For example, if s[i] = 'a' and nums[0] = 3, the character 'a' transforms into the next 3 consecutive characters ahead of it, which results in "bcd".
The transformation wraps around the alphabet if it exceeds 'z'. For example, if s[i] = 'y' and nums[24] = 3, the character 'y' transforms into the next 3 consecutive characters ahead of it, which results in "zab".
Return the length of the resulting string after exactly t transformations.

Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]

Output: 7

Explanation:

First Transformation (t = 1):

'a' becomes 'b' as nums[0] == 1
'b' becomes 'c' as nums[1] == 1
'c' becomes 'd' as nums[2] == 1
'y' becomes 'z' as nums[24] == 1
'y' becomes 'z' as nums[24] == 1
String after the first transformation: "bcdzz"
Second Transformation (t = 2):

'b' becomes 'c' as nums[1] == 1
'c' becomes 'd' as nums[2] == 1
'd' becomes 'e' as nums[3] == 1
'z' becomes 'ab' as nums[25] == 2
'z' becomes 'ab' as nums[25] == 2
String after the second transformation: "cdeabab"
Final Length of the string: The string is "cdeabab", which has 7 characters.

Example 2:

Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]

Output: 8

Explanation:

First Transformation (t = 1):

'a' becomes 'bc' as nums[0] == 2
'z' becomes 'ab' as nums[25] == 2
'b' becomes 'cd' as nums[1] == 2
'k' becomes 'lm' as nums[10] == 2
String after the first transformation: "bcabcdlm"
Final Length of the string: The string is "bcabcdlm", which has 8 characters.

 

Constraints:

1 <= s.length <= 105
s consists only of lowercase English letters.
1 <= t <= 109
nums.length == 26
1 <= nums[i] <= 25
*/ 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
    int MOD = 1e9 + 7;

    Matrix matrixMultiplication(const Matrix& A, const Matrix& B) {
        Matrix result(26, vector<int>(26, 0));
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                for (int k = 0; k < 26; ++k) {
                    result[i][j] = (result[i][j] + (1LL * A[i][k] * B[k][j]) % MOD) % MOD;
                }
            }
        }
        return result;
    }

    Matrix matrixExponentiation(const Matrix& base, int exponent) {

        if (exponent == 0) {
            Matrix identity(26, vector<int>(26, 0));
            for (int i = 0; i < 26; ++i)
                identity[i][i] = 1;
            return identity;
        }

        Matrix half   = matrixExponentiation(base, exponent / 2);
        Matrix result = matrixMultiplication(half, half);

        if (exponent % 2 == 1)
            result = matrixMultiplication(result, base);

        return result;
    }

public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector<int> freq(26, 0);
        for (char &ch : s) {
            freq[ch - 'a']++;
        }

        Matrix T(26, vector<int>(26, 0));
        for (int i = 0; i < 26; ++i) {
            for (int add = 1; add <= nums[i]; ++add)
                T[(i + add) % 26][i]++;
        }

        Matrix result = matrixExponentiation(T, t);

        vector<int> updated_freq(26, 0);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j)
                updated_freq[i] = (updated_freq[i] + (1LL * result[i][j] * freq[j]) % MOD) % MOD;
        }

        int resultLength = 0;
        for (int i = 0; i < 26; ++i)
            resultLength = (resultLength + updated_freq[i]) % MOD;

        return resultLength;
    }

