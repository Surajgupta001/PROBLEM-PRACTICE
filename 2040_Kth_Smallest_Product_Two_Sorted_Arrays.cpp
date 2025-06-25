/*
2040. Kth Smallest Product of Two Sorted Arrays - [Leetcode - 2040(Hard)]
--------------------------------------------------------------------------
Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.


Example 1:

Input: nums1 = [2,5], nums2 = [3,4], k = 2
Output: 8
Explanation: The 2 smallest products are:
- nums1[0] * nums2[0] = 2 * 3 = 6
- nums1[0] * nums2[1] = 2 * 4 = 8
The 2nd smallest product is 8.
Example 2:

Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
Output: 0
Explanation: The 6 smallest products are:
- nums1[0] * nums2[1] = (-4) * 4 = -16
- nums1[0] * nums2[0] = (-4) * 2 = -8
- nums1[1] * nums2[1] = (-2) * 4 = -8
- nums1[1] * nums2[0] = (-2) * 2 = -4
- nums1[2] * nums2[0] = 0 * 2 = 0
- nums1[2] * nums2[1] = 0 * 4 = 0
The 6th smallest product is 0.
Example 3:

Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
Output: -6
Explanation: The 3 smallest products are:
- nums1[0] * nums2[4] = (-2) * 5 = -10
- nums1[0] * nums2[3] = (-2) * 4 = -8
- nums1[4] * nums2[0] = 2 * (-3) = -6
The 3rd smallest product is -6.


Constraints:

1 <= nums1.length, nums2.length <= 5 * 104
-105 <= nums1[i], nums2[j] <= 105
1 <= k <= nums1.length * nums2.length
nums1 and nums2 are sorted.
*/

#include <iostream>
#include <vector>
using namespace std;

long long findCountSmallest(vector<int> &nums1, vector<int> &nums2, long long midProduct){
    long long productsCount = 0;

    int n = nums2.size();

    for (int i = 0; i < nums1.size(); i++){ // nums1[i]

        if (nums1[i] >= 0){
            int l = 0;
            int r = n - 1;
            int m = -1; // invalid index on left hand side

            while (l <= r){
                int mid = l + (r - l) / 2;
                long long product = 1LL * nums1[i] * nums2[mid];

                if (product <= midProduct){
                    m = mid;
                    l = mid + 1;
                }
                else{
                    r = mid - 1;
                }
            }
            productsCount += (m + 1); // covered by nums1[i]
        }
        else{
            // product will be negative and right hand side will contain smaller products and left hand side larger
            int l = 0;
            int r = n - 1;
            int m = n; // invalid index on the right hand side

            while (l <= r){
                int mid = l + (r - l) / 2;
                long long product = 1LL * nums1[i] * nums2[mid];

                if (product <= midProduct){
                    m = mid;
                    r = mid - 1;
                }
                else{
                    l = mid + 1;
                }
            }

            productsCount += (n - m);
        }
    }
    return productsCount;
}

long long kthSmallestProduct(vector<int> &nums1, vector<int> &nums2, long long k){
    long long result = 0;

    long long l = -1e10; // min product possible
    long long r = 1e10;  // max product possible

    while (l <= r){
        long long midProduct = l + (r - l) / 2;

        // check if this is kth smallest or not

        long long countSmallest = findCountSmallest(nums1, nums2, midProduct);

        if (countSmallest >= k){
            result = midProduct;
            r = midProduct - 1;
        }
        else{
            l = midProduct + 1;
        }
    }
    return result;
}