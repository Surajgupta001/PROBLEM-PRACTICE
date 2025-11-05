/*
Find X-Sum of All K-Long Subarrays II - [Leetcode - 3321(Hard)]
----------------------------------------------------------------
You are given an array nums of n integers and two integers k and x.

The x-sum of an array is calculated by the following procedure:

=> Count the occurrences of all elements in the array.
=> Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
=> Calculate the sum of the resulting array.
=> Note that if an array has less than x distinct elements, its x-sum is the sum of the array.

Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].

Example 1:

Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2

Output: [6,10,12]

Explanation:

For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
Example 2:

Input: nums = [3,8,7,8,7,5], k = 2, x = 2

Output: [11,15,15,15,12]

Explanation:

Since k == x, answer[i] is equal to the sum of the subarray nums[i..i + k - 1].

Constraints:

nums.length == n
1 <= n <= 10^5
1 <= nums[i] <= 10^9
1 <= x <= k <= nums.length
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

set<pair<int, int>> mainSet; // {freq, element} - top x frequent, elements
set<pair<int, int>> secondarySet; // {freq, element} - rest of the frequent, elements

long long sum = 0; // Maintain sum of top x elements from main set
int X = 0; // global x value used by helper functions

void insertIntoSet(const pair<int, int> &p){
    if(mainSet.size() < X || p > *mainSet.begin()){
        sum += p.first * 1LL * p.second;
        mainSet.insert(p);

        if(mainSet.size() > X){
            auto smallestInMain = *mainSet.begin();
            sum -= smallestInMain.first * 1LL * smallestInMain.second;
            mainSet.erase(mainSet.begin());
            secondarySet.insert(smallestInMain);
        }
    }
    else {
        secondarySet.insert(p);
    }
}

void removeFromSet(const pair<int, int> &p){
    if(mainSet.find(p) != mainSet.end()){
        sum -= p.first * 1LL * p.second;
        mainSet.erase(p);

        if(!secondarySet.empty()){
            auto largestInSecondary = *secondarySet.rbegin();
            secondarySet.erase(largestInSecondary);
            mainSet.insert(largestInSecondary);
            sum += largestInSecondary.first * 1LL * largestInSecondary.second;
        }
    }
    else {
        secondarySet.erase(p);
    }
}

vector<long long> findXSum(vector<int>& nums, int k, int x) {
    int n = nums.size();

    // Reset all globals for this invocation
    mainSet.clear();
    secondarySet.clear();
    sum = 0;
    X = x;

    vector<long long> result;
    unordered_map<int, int> freqMap; // element -> frequency

    int i = 0;
    int j = 0;

    while (j < n) {
        if (freqMap[nums[j]] > 0) {
            removeFromSet({freqMap[nums[j]], nums[j]});   // remove old (freq, val)
        }

        freqMap[nums[j]]++;                               // new freq
        insertIntoSet({freqMap[nums[j]], nums[j]});       // add updated (freq, val)

        if (j - i + 1 == k) {
            result.push_back(sum);

            // slide window: remove nums[i]
            removeFromSet({freqMap[nums[i]], nums[i]});
            freqMap[nums[i]]--;
            if (freqMap[nums[i]] == 0) {
                freqMap.erase(nums[i]);
            } else {
                insertIntoSet({freqMap[nums[i]], nums[i]});
            }
            ++i;
        }
        ++j;
    }
    return result;
}

int main() {
    vector<int> nums1 = {1,1,2,2,3,4,2,3};
    int k1 = 6, x1 = 2;
    vector<long long> result1 = findXSum(nums1, k1, x1);
    for (long long val : result1) {
        cout << val << " "; // Output: 6 10 12
    }
    cout << endl;

    vector<int> nums2 = {3,8,7,8,7,5};
    int k2 = 2, x2 = 2;
    vector<long long> result2 = findXSum(nums2, k2, x2);
    for (long long val : result2) {
        cout << val << " "; // Output: 11 15 15 15 12
    }
    cout << endl;

    return 0;
}