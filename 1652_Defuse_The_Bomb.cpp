/*
Defuse The Bomb - [Leetcode - 1652(Easy)]
=============================================
You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.

To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.

If k > 0, replace the ith number with the sum of the next k numbers.
If k < 0, replace the ith number with the sum of the previous k numbers.
If k == 0, replace the ith number with 0.
As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].

Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!

Example 1:

Input: code = [5,7,1,4], k = 3
Output: [12,10,16,13]
Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

Example 2:

Input: code = [1,2,3,4], k = 0
Output: [0,0,0,0]
Explanation: When k is zero, the numbers are replaced by 0. 

Example 3:

Input: code = [2,4,9,3], k = -2
Output: [12,5,6,13]
Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4]. Notice that the numbers wrap around again. If k is negative, the sum is of the previous numbers.

======== What is a Circular Array? ==============
A circular array, also known as a ring buffer or circular buffer, is a data structure that uses a single array to implement a queue or a buffer. It is called "circular" because the last element of the array is connected to the first element, forming a circle.

The circular array has the following properties:
- It is a fixed-size array.
- It is a queue or a buffer.
- It is a circular data structure.
*/ 

#include <iostream>
#include <vector>
using namespace std;


// Brute Force
vector<int> decrypt(vector<int>& code, int k){
    /*
    *Time : O(n^2);
    *Space: O(n)
    */  
    int n = code.size();
    k = k % n; // Handle cases where k is greater than n

    // If k is zero, return a vector of zeros
    if(k == 0){
        vector<int> ans(n, 0);
        return ans;
    }
    vector<int> ans(n);
    for(int i=0; i<n; i++){
        int sum = 0;
        // Calculate the sum if the next k numbers
        if(k > 0){
            for(int j=1; j<=k; j++){
                int idx =(i + j) % n;
                sum += code[idx];
            }
        }
        // Calculate the sum of the previous k numbers
        else{
            for(int j=1; j<=(-k); j++){
                int idx =(i + n + j) % n;
                sum += code[idx];
            }
        }
        ans[i] = sum;
    }
    return ans;
}
/*
Step-by-Step Calculation: DRY RUN
For i = 0:
k = 3 (positive), so we sum the next 3 elements:
code[(0 + 1) % 4] = code[1] = 4
code[(0 + 2) % 4] = code[2] = 9
code[(0 + 3) % 4] = code[3] = 3
Sum: 4 + 9 + 3 = 16

ans[0] = 16

For i = 1:
k = 3 (positive), so we sum the next 3 elements:
code[(1 + 1) % 4] = code[2] = 9
code[(1 + 2) % 4] = code[3] = 3
code[(1 + 3) % 4] = code[0] = 2
Sum: 9 + 3 + 2 = 14

ans[1] = 14

For i = 2:
k = 3 (positive), so we sum the next 3 elements:
code[(2 + 1) % 4] = code[3] = 3
code[(2 + 2) % 4] = code[0] = 2
code[(2 + 3) % 4] = code[1] = 4
Sum: 3 + 2 + 4 = 9

ans[2] = 9

For i = 3:
k = 3 (positive), so we sum the next 3 elements:
code[(3 + 1) % 4] = code[0] = 2
code[(3 + 2) % 4] = code[1] = 4
code[(3 + 3) % 4] = code[2] = 9
Sum: 2 + 4 + 9 = 15

ans[3] = 15
*/ 

// =========== Optimised Cod ==============
vector<int> decrypt(vector<int>& code, int k){
    /*
    * Time : O(n);
    * Space : O(n);
    */ 
    int n = code.size();
    vector<int> ans(n, 0);
    if (k == 0) return ans;

    // Using prefix sum array
    vector<int> prefix(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        prefix[i + 1] = prefix[i] + code[i % n];
    }

    // Using sliding window to evualte the sum
    for (int i = 0; i < n; i++) {
        if (k > 0) {
            // Sum of next k elements
            ans[i] = prefix[i + k + 1] - prefix[i + 1];
        }
        else {
            // Sum of previous k elements
            ans[i] = prefix[i + n] - prefix[i + n + k];
        }
    }
    return ans;
}
/*
======== DRY RUN ===========

Prefix Sum Array:
==> We create a prefix sum array of size 2 * n + 1 to handle the circular nature of the array.
==> The prefix sum array is computed as:
    prefix[i] = sum of all elements from code[0] to code[i-1]
==> For example, if code = [2, 4, 9, 3], the prefix sum array will be:
    prefix = [0, 2, 6, 15, 18, 20, 24, 33, 36]

Sliding Window:
==> For each index i in the array:
    ==> If k > 0, the sum of the next k elements is:
        sum = prefix[i + k + 1] - prefix[i + 1]
    ==> If k < 0, the sum of the previous k elements is:
        sum = prefix[i + n] - prefix[i + n + k]

Circular Handling:
==> The modulo arithmetic (i % n) ensures that the array is treated as circular.

Calculations:
For i = 0:
Sum of next 3 elements:
sum = prefix[0 + 3 + 1] - prefix[0 + 1] = prefix[4] - prefix[1] = 18 - 2 = 16

ans[0] = 16

For i = 1:
Sum of next 3 elements:
sum = prefix[1 + 3 + 1] - prefix[1 + 1] = prefix[5] - prefix[2] = 20 - 6 = 14

ans[1] = 14

For i = 2:
Sum of next 3 elements:
sum = prefix[2 + 3 + 1] - prefix[2 + 1] = prefix[6] - prefix[3] = 24 - 15 = 9

ans[2] = 9

For i = 3:
Sum of next 3 elements:
sum = prefix[3 + 3 + 1] - prefix[3 + 1] = prefix[7] - prefix[4] = 33 - 18 = 15
ans[3] = 15

*/ 
int main(){
    vector<int> code = {2,4,9,3};
    int k = 3;
    vector<int> ans = decrypt(code, k);
    cout<<"The decrypted code is: ";
    for(int num : ans){
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}