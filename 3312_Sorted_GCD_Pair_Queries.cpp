/*
Sorted GCD Pair Queries - [Leetcode - 3312(Hard)]
----------------------------------------------------
You are given an integer array nums of length n and an integer array queries.

Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.

For each query queries[i], you need to find the element at index queries[i] in gcdPairs.

Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.

The term gcd(a, b) denotes the greatest common divisor of a and b.

Example 1:

Input: nums = [2,3,4], queries = [0,2,2]

Output: [1,2,2]

Explanation:

gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].

After sorting in ascending order, gcdPairs = [1, 1, 2].

So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].

Example 2:

Input: nums = [4,4,2,1], queries = [5,3,1,0]

Output: [4,2,1,1]

Explanation:

gcdPairs sorted in ascending order is [1, 1, 1, 2, 2, 4].

Example 3:

Input: nums = [2,2], queries = [0,0]

Output: [2,2]

Explanation:

gcdPairs = [2].

Constraints:

2 <= n == nums.length <= 10^5
1 <= nums[i] <= 5 * 10^4
1 <= queries.length <= 10^5
0 <= queries[i] < n * (n - 1) / 2
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> gcdValues(vector<int> &nums, vector<long long> &queries) {
    int n = nums.size();
    int maxValue = *max_element(nums.begin(), nums.end());

    vector<int> divisorFrequency(maxValue + 1, 0);
    for(int i=0; i<n; i++){
        int num = nums[i];
        for(int j=1; j<=sqrt(num); j++){
            if(num % j == 0){
                divisorFrequency[j]++;
                if(j != num / j){
                    divisorFrequency[num / j]++;
                }
            }
        }
    }

    vector<long long> pairsWithGCD(maxValue + 1, 0);
    for(int factor=maxValue; factor>=1; factor--){
        long long count = divisorFrequency[factor];
        // nc2 -> number of pairs with GCD equal to factor
        pairsWithGCD[factor] = (count * (count - 1)) / 2;
        
        // Correction for multiples of the factor
        for(int multiple = 2 * factor; multiple <= maxValue; multiple += factor){
            pairsWithGCD[factor] -= pairsWithGCD[multiple];
        }
    }

    vector<long long> prefixCountGCD(maxValue + 1, 0);
    for(int factor=1; factor <= maxValue; factor++){
        prefixCountGCD[factor] = prefixCountGCD[factor - 1] + pairsWithGCD[factor];
    }

    // Binary search for each query
    vector<int> result;
    for(auto &idx : queries){
        int low = 1;
        int high = maxValue;

        int temp = 1;

        while(low <= high){
            int mid_gcd = low + (high - low) / 2;
            if(prefixCountGCD[mid_gcd] > idx){
                temp = mid_gcd;
                high = mid_gcd - 1;
            } else {
                low = mid_gcd + 1;
            }
        }
        result.push_back(temp);
    }

    return result;
}

int main () {
    vector<int> nums1 = {2, 3, 4};
    vector<long long> queries1 = {0, 2, 2};
    vector<int> result1 = gcdValues(nums1, queries1);
    for(int val : result1) {
        cout << val << " "; // Output: 1 2 2
    }
    cout << endl;

    vector<int> nums2 = {4, 4, 2, 1};
    vector<long long> queries2 = {5, 3, 1, 0};
    vector<int> result2 = gcdValues(nums2, queries2);
    for(int val : result2) {
        cout << val << " "; // Output: 4 2 1 1
    }
    cout << endl;

    vector<int> nums3 = {2, 2};
    vector<long long> queries3 = {0, 0};
    vector<int> result3 = gcdValues(nums3, queries3);
    for(int val : result3) {
        cout << val << " "; // Output: 2 2
    }
    cout << endl;

    return 0;
}