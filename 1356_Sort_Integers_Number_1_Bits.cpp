/*
Sort Integers by The Number of 1 Bits - [Leetcode - 1356(Easy)]
-------------------------------------------------------------------
You are given an integer array arr. Sort the integers in the array in ascending order by the number of 1's in their binary representation and in case of two or more integers have the same number of 1's you have to sort them in ascending order.

Return the array after sorting it.

Example 1:

Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explantion: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]

Example 2:

Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
Output: [1,2,4,8,16,32,64,128,256,512,1024]
Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.

Constraints:

1 <= arr.length <= 500
0 <= arr[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach - 1 : Using built-in function __builtin_popcount to count the number of 1 bits in the binary representation of each integer.
vector<int> sortByBits(vector<int>& arr) {
    sort(begin(arr), end(arr), [](int a, int b) {
        int countA = __builtin_popcount(a);
        int countB = __builtin_popcount(b);
        if (countA == countB) {
            return a < b;
        }
        return countA < countB;
    });
    return arr;
}

// Approach - 2 : Using a custom comparator function
// Function to count number of 1 bits
static int countOneBits(int num) {
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

// Custom comparator
static bool customComparator(int a, int b) {
    int count_A = countOneBits(a);
    int count_B = countOneBits(b);

    if (count_A == count_B) {
        return a < b;        // if same number of 1s, sort by value
    }
    return count_A < count_B; // otherwise sort by number of 1s
}

// Function to sort array
vector<int> sortByBits(vector<int> arr) {
    sort(arr.begin(), arr.end(), customComparator);
    return arr;
}

// Approach - 3 : Lambda function with built-in function
int countOneBits(int num) {
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
vector<int> sortByBits(vector<int> arr) {
    auto lambda = [&](int a, int b) {
        int countA = countOneBits(a);
        int countB = countOneBits(b);
        if (countA == countB) {
            return a < b;
        }
        return countA < countB;
    };
    sort(arr.begin(), arr.end(), lambda);
    return arr;
}


int main() {
    vector<int> arr1 = {0,1,2,3,4,5,6,7,8};
    vector<int> result1 = sortByBits(arr1);
    cout << "Result 1: ";
    for (int x : result1) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<int> arr2 = {1024,512,256,128,64,32,16,8,4,2,1};
    vector<int> result2 = sortByBits(arr2);
    cout << "Result 2: ";
    for (int x : result2) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}