/*
Find X-Sum of All K-Long Subarrays I - [Leetcode - 3318(Easy)]
----------------------------------------------------------------
You are given an array nums of n integers and two integers k and x.

The x-sum of an array is calculated by the following procedure:

• Count the occurrences of all elements in the array.
• Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
• Calculate the sum of the resulting array.

Note that if an array has less than x distinct elements, its x-sum is the sum of the array.

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

1 <= n == nums.length <= 50
1 <= nums[i] <= 50
1 <= x <= k <= nums.length
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

// Approach 1: Simulation (Brute Force) - O(n * k log k) time complexity
vector<int> findXSum(vector<int>& nums, int k, int x) {
    int n = nums.size();
    vector<int> answer(n - k + 1);
    for (int i = 0; i <= n - k; i++) {
        unordered_map<int, int> freq;
        for (int j = i; j < i + k; j++) {
            freq[nums[j]]++;
        }
        vector<pair<int, int>> elements(freq.begin(), freq.end());
        sort(elements.begin(), elements.end(), [](pair<int, int>& a, pair<int, int>& b) {
            if (a.second == b.second) return a.first > b.first;
            return a.second > b.second;
        });
        int sum = 0;
        for (int j = 0; j < min(x, (int)elements.size()); j++) {
            sum += elements[j].first * elements[j].second;
        }
        answer[i] = sum;
    }
    return answer;
}

//Approach (Using max-heap + sliding window)
//T.C : O(n * k * log(k))
//S.C : O(k)
int findTopXSum(unordered_map<int, int>& mp, int x) {
    // Min-heap to store top x frequent elements
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //freq, element
    
    for(auto &it : mp) { //O(k * log(k))
        pq.push({it.second, it.first});
        if(pq.size() > x) {
            pq.pop(); //remove smallest element from the top of min-heap
        }
    }
    
    int sum = 0;
    while(!pq.empty()) { //K
        sum += pq.top().first * pq.top().second; // freq * element
        pq.pop();
    }
    return sum;
}

vector<int> findXSum(vector<int>& nums, int k, int x) {
    int n = nums.size();
    
    unordered_map<int, int> mp; //O(k)
    vector<int> result;
    
    int i = 0;
    int j = 0;
    
    //T.C : O(n * klogk)
    while(j < n) { // Standard sliding window
        mp[nums[j]]++;
        if(j - i + 1 == k) {
            result.push_back(findTopXSum(mp, x));
            mp[nums[i]]--;
            if(mp[nums[i]] == 0) {
                mp.erase(nums[i]);
            }
            i++;
        }
        j++;
    }
    return result;
}

    
int main(){
    vector<int> nums = {1,1,2,2,3,4,2,3};
    int k = 6, x = 2;
    vector<int> result = findXSum(nums, k, x);
    for (int val : result) {
        cout << val << " ";
    }
    return 0;
}