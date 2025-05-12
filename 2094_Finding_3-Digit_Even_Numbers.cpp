/*
Finding 3-Digit Even Numbers - [Leetcode - 2094(Easy)]
-------------------------------------------------------
You are given an integer array digits, where each element is a digit. The array may contain duplicates.

You need to find all the unique integers that follow the given requirements:

The integer consists of the concatenation of three elements from digits in any arbitrary order.
The integer does not have leading zeros.
The integer is even.
For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.

Return a sorted array of the unique integers.

Example 1:

Input: digits = [2,1,3,0]
Output: [102,120,130,132,210,230,302,310,312,320]
Explanation: All the possible integers that follow the requirements are in the output array.
Notice that there are no odd integers or integers with leading zeros.

Example 2:

Input: digits = [2,2,8,8,2]
Output: [222,228,282,288,822,828,882]
Explanation: The same digit can be used as many times as it appears in digits.
In this example, the digit 8 is used twice each time in 288, 828, and 882.
Example 3:

Input: digits = [3,7,5]
Output: []
Explanation: No even integers can be formed using the given digits.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Approach 1 : Brute Force
// Time Complexity : O(n^3) where n is the size of digits
vector<int> findEvenNumbers(vector<int> &digits){
    set<int> st; // To avoid duplicates and also to sort the numbers
    int n = digits.size();

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){

                if (i == j || j == k || i == k)continue; // Skip if any two indices are same

                int num = digits[i] * 100 + digits[j] * 10 + digits[k]; // Form the number

                if (num >= 100 and num % 2 == 0){ // Check if it's a 3-digit even number
                    st.insert(num); // Insert into set to avoid duplicates
                }
            }
        }
    }
    vector<int> ans(st.begin(), st.end()); // Convert set to vector
    return ans;
}

// Approach 2 : Better Approach
vector<int> findEvenNumbers(vector<int> &digits){
    vector<int> ans;
    vector<int> freq(10, 0); // Frequency array to count digits

    for (int digit : digits){
        freq[digit]++;
    }

    for (int i = 1; i <= 9; i++){
        
        if (freq[i] == 0) continue; // Skip if digit is not present
        freq[i]--;    // Decrease frequency of the first digit
        
        for (int j = 0; j <= 9; j++){
            
            if (freq[j] == 0) continue; // Skip if digit is not present
            freq[j]--;    // Decrease frequency of the second digit
            
            for (int k = 0; k <= 8; k += 2){
                
                if (freq[k] == 0) continue; // Skip if digit is not present
                freq[k]--;    // Decrease frequency of the third digit

                int num = i * 100 + j * 10 + k; // Form the number
                ans.push_back(num); // Add to result

                freq[k]++; // Restore frequency of the third digit
            }
            freq[j]++; // Restore frequency of the second digit
        }
        freq[i]++; // Restore frequency of the first digit
    }
    return ans;
}

int main(){

    vector<int> digits = {2, 1, 3, 0};
    vector<int> result = findEvenNumbers(digits);

    cout << "Unique 3-digit even numbers: ";
    for (int num : result){
        cout << num << " ";
    }
    cout << endl;

    return 0;
}