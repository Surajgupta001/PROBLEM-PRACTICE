/*
Sliding Window Maximum - [Leetcode - 239(Hard)]
------------------------------------------------
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]

Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:

Input: nums = [1], k = 1
Output: [1]

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length

Similar Problem => 1425. Constrained Subsequence Sum
Also U can solve Priority Queue approach using max heap
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

/*
Steps 1. When new element comes in, make sapce for it (window size can't be greater than k)
Steps 2. Now, When nums[i] comes, there is no need to keep small elements in the window, pop them
Steps 3. Now push i in deque -> for nums[i]
Steps 4. If(i >= k - 1) then dq.front() is our answer for that window
*/ 

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> ans;

    for(int i = 0; i < nums.size(); i++) {
        // Remove indices out of current window
        if(!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        // Remove indices whose corresponding values are less than nums[i]
        while(!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        // The front of the deque is the largest element's index for the window
        if(i >= k - 1) {
            ans.push_back(nums[dq.front()]);
        }
    }
    return ans;
}

// Alternative approach using priority queue
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    priority_queue<pair<int, int>> pq; // {value, index}
    vector<int> ans;

    for (int i = 0; i < nums.size(); ++i) {
        pq.push({nums[i], i});
        // Remove elements outside the window
        while (!pq.empty() && pq.top().second <= i - k) {
            pq.pop();
        }
        if (i >= k - 1) {
            ans.push_back(pq.top().first);
        }
    }
    return ans;
}

int main(){

    vector<int> nums = {1,3,-1,-3,5,3,6,7};

    int k = 3;

    vector<int> result = maxSlidingWindow(nums, k);

    for(int i=0; i<result.size(); i++){
        cout<<result[i]<<" ";
    }
    cout<<endl;

    return 0;
}