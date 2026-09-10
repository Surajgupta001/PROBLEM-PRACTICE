/*
Construct Uniform Parity Array II - [Leetcode - 3876(Medium)]
-----------------------------------------------------------------
You are given an array nums1 of n distinct integers.

You want to construct another array nums2 of length n such that the elements in nums2 are either all odd or all even.

For each index i, you must choose exactly one of the following (in any order):

nums2[i] = nums1[i]​​​​​​​
nums2[i] = nums1[i] - nums1[j], for an index j != i, such that nums1[i] - nums1[j] >= 1
Return true if it is possible to construct such an array, otherwise return false.
 

Example 1:

Input: nums1 = [1,4,7]

Output: true

Explanation:​​​​​​​​​​​​​​

Set nums2[0] = nums1[0] = 1.
Set nums2[1] = nums1[1] - nums1[0] = 4 - 1 = 3.
Set nums2[2] = nums1[2] = 7.
nums2 = [1, 3, 7], and all elements are odd. Thus, the answer is true.
Example 2:

Input: nums1 = [2,3]

Output: false

Explanation:

It is not possible to construct nums2 such that all elements have the same parity. Thus, the answer is false.

Example 3:

Input: nums1 = [4,6]

Output: true

Explanation:

Set nums2[0] = nums1[0] = 4.
Set nums2[1] = nums1[1] = 6.
nums2 = [4, 6], and all elements are even. Thus, the answer is true.
 

Constraints:

1 <= n == nums1.length <= 10^5
1 <= nums1[i] <= 10^9
nums1 consists of distinct integers.
*/

#include <iostream>
#include <vector>
using namespace std;

bool uniformArray(vector<int>& nums1) {
    int minElement = *min_element(nums1.begin(), nums1.end());

    if(minElement % 2 == 1){ // odd - then all elements can be made odd
        return true;
    }

    // Check if all elements are even in nums2
    for(int i = 0; i < nums1.size(); i++){
        if(nums1[i] % 2 == 1){ // if any element is odd, we cannot make all even
            return false;
        }
    }

    return true; // all elements are even, we can make all even
}

int main() {
    vector<int> nums1 = {1, 4, 7};
    cout << (uniformArray(nums1) ? "true" : "false") << endl; // Output: true

    nums1 = {2, 3};
    cout << (uniformArray(nums1) ? "true" : "false") << endl; // Output: false

    nums1 = {4, 6};
    cout << (uniformArray(nums1) ? "true" : "false") << endl; // Output: true

    return 0;
}