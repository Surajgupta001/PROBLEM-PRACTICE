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

// Function to convert a number to base k
string convertToBaseK(long long num, int k) {
    if (num == 0) return "0"; // Handle the case for zero
    string result = "";
    while (num > 0) {
        result += to_string(num % k);
        num /= k;
    }
    reverse(result.begin(), result.end()); // Reverse to get the correct order
    return result;
}

// Function to check if a string is a palindrome
bool isPalindrome(const string &baseK) {
    int left = 0;
    int right = baseK.size() - 1;
    
    while (left < right) {
        if (baseK[left] != baseK[right]) return false; // If characters don't match, it's not a palindrome
        left++;
        right--;
    }
    return true; // If all characters match, it'baseK a palindrome
}


long long kMirror (int k, int n ) {
    long long sum = 0;
    int length = 1; // Create L length plindromes

    while(n > 0) {
        int half_length = (length + 1) / 2; // Half length of the palindrome

        long long min_num = pow(10, half_length - 1); // Minimum half palindrome
        long long max_num = pow(10, half_length) - 1; // Maximum half palindrome

        for(int num = min_num; num <= max_num; num++) {
            string first_half = to_string(num);
            string second_half = first_half;
            reverse(second_half.begin(), second_half.end()); // Create the second half of the palindrome

            string palindrome_str = "";
            if(length % 2 == 0) {
                palindrome_str = first_half + second_half; // Even length palindrome
            } else {
                palindrome_str = first_half + second_half.substr(1); // Odd length palindrome
            }

            long long palindrome_num = stoll(palindrome_str); // Convert to long long

            string baseK = convertToBaseK(palindrome_num, k); // Convert to base k

            if(isPalindrome(baseK)) { // Check if it's a k-mirror number
                sum += palindrome_num; // Add to the sum and found one k-mirror number
                n--; // Decrease the count of k-mirror numbers found
                if(n == 0) break; // Stop if we found enough k-mirror numbers
            }
        } 
        length++; // Increase the length of the palindrome
    }
    return sum; // Return the total sum of k-mirror numbers
}

int main() {
    int k, n;
    cout << "Enter base k (2 <= k <= 9): ";
    cin >> k;
    cout << "Enter number of k-mirror numbers n (1 <= n <= 30): ";
    cin >> n;

    long long result = kMirror(k, n);
    cout << "Sum of the " << n << " smallest k-mirror numbers in base " << k << " is: " << result << endl;

    return 0;
}