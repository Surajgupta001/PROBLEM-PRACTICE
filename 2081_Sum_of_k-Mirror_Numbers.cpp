/*
Sum of k-Mirror Numbers - [Leetcode - 2081(Hard)]
--------------------------------------------------
A k-mirror number is a positive integer without leading zeros that reads the same both forward and backward in base-10 as well as in base-k.

For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and 1001 respectively, which read the same both forward and backward.
On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which does not read the same both forward and backward.
Given the base k and the number n, return the sum of the n smallest k-mirror numbers.



Example 1:

Input: k = 2, n = 5
Output: 25
Explanation:
The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
  base-10    base-2
    1          1
    3          11
    5          101
    7          111
    9          1001
Their sum = 1 + 3 + 5 + 7 + 9 = 25.
Example 2:

Input: k = 3, n = 7
Output: 499
Explanation:
The 7 smallest 3-mirror numbers are and their representations in base-3 are listed as follows:
  base-10    base-3
    1          1
    2          2
    4          11
    8          22
    121        11111
    151        12121
    212        21212
Their sum = 1 + 2 + 4 + 8 + 121 + 151 + 212 = 499.
Example 3:

Input: k = 7, n = 17
Output: 20379000
Explanation: The 17 smallest 7-mirror numbers are:
1, 2, 3, 4, 5, 6, 8, 121, 171, 242, 292, 16561, 65656, 2137312, 4602064, 6597956, 6958596


Constraints:

2 <= k <= 9
1 <= n <= 30

*/

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

bool isPalindrome(string baseK){
    int i = 0;
    int j = baseK.length() - 1;

    while (i <= j){
        if (baseK[i] != baseK[j]){
            return false;
        }
        i++;
        j--;
    }

    return true;
}

string convertToBaseK(long long num, int k){
    if (num == 0){
        return "0";
    }

    string res = "";
    while (num > 0){
        res += to_string(num % k);
        num /= k;
    }

    return res;
}

long long kMirror(int k, int n){
    long long sum = 0;
    int L = 1; // create L length palindromes

    while (n > 0){
        int half_length = (L + 1) / 2;

        long long min_num = pow(10, half_length - 1);
        long long max_num = pow(10, half_length) - 1;

        for (int num = min_num; num <= max_num; num++){
            string first_half = to_string(num);
            string second_half = first_half;
            reverse(begin(second_half), end(second_half));

            string pal = "";
            if (L % 2 == 0){ // even length palindrome
                pal = first_half + second_half;
            }
            else{ // off length palindrome
                pal = first_half + second_half.substr(1);
            }

            long long pal_num = stoll(pal);

            string baseK = convertToBaseK(pal_num, k);

            if (isPalindrome(baseK)){
                sum += pal_num; // found one k-mirror number
                n--;
                if (n == 0){
                    break;
                }
            }
        }

        L++;
    }

    return sum;
}