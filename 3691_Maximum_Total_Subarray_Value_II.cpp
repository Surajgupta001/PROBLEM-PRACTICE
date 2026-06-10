/*
Maximum Total Subarray Value II - [Leetcode - 3691(Hard)]
-----------------------------------------------------------
You are given an integer array nums of length n and an integer k.

You must select exactly k distinct subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

Example 1:

Input: nums = [1,3,2], k = 2

Output: 4

Explanation:

One optimal approach is:

Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:

Input: nums = [4,2,5,1], k = 3

Output: 12

Explanation:

One optimal approach is:

Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.

Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​^4
0 <= nums[i] <= 10^9
1 <= k <= min(10^5, n * (n + 1) / 2)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
using namespace std;

#define ll long long

class SegmentTree {
private:

    vector<ll> segmentTree;
    bool isMinTree; // true -> min Segment Tree, false -> max Segment Tree

    void buildSegmentTree(int i, int l, int r, vector<int> &nums) {
        if(l == r) {
            segmentTree[i] = nums[l]; // Leaf node
            return;
        }

        int mid = (l + r) / 2; // Mid point of the current segment

        buildSegmentTree(2*i + 1, l, mid, nums); // Build left child
        buildSegmentTree(2*i + 2, mid + 1, r, nums); // Build right child

        // Internal node value is either the minimum or maximum of its children based on the type of segment tree
        if(isMinTree) { // Internal node value is the minimum of its children
            segmentTree[i] = min(segmentTree[2*i + 1], segmentTree[2*i + 2]); // Internal node value is the minimum of its children
        } else {
            segmentTree[i] = max(segmentTree[2*i + 1], segmentTree[2*i + 2]); // Internal node value is the maximum of its children
        }
    }

    ll querySegmentTree(int start, int end, int node, int l, int r) {
        // No overlap
        if(r < start || end < l) {
            return isMinTree ? LLONG_MAX : LLONG_MIN;
        }

        // Complete overlap
        if(l <= start && end <= r) {
            return segmentTree[node];
        }

        // Partial overlap
        int mid = (start + end) / 2;

        ll leftChild = querySegmentTree(start, mid, 2*node + 1, l, r);
        ll rightChild = querySegmentTree(mid + 1, end, 2*node + 2, l, r);

        if(isMinTree) {
            return min(leftChild, rightChild);
        } else {
            return max(leftChild, rightChild);
        }
    }

public:

    SegmentTree(vector<int> &nums, bool flag) {
        int n = nums.size();
        isMinTree = flag;

        // The size of the segment tree array is typically 4 times the size of the input array to accommodate all nodes.
        segmentTree.resize(4 * n);
        buildSegmentTree(0, 0, n - 1, nums);
    }

    // Query the segment tree for the minimum or maximum value in the range [l, r]
    ll query(int l, int r, int n) {
        return querySegmentTree(0, n - 1, 0, l, r);
    }
};

// Helper function to calculate the value of a subarray nums[l..r] using the segment trees
ll getValue(int l, int r, SegmentTree &minSegmentTree, SegmentTree &maxSegmentTree, int n) {
    ll minElement = minSegmentTree.query(l, r, n);
    ll maxElement = maxSegmentTree.query(l, r, n);
    return maxElement - minElement;
}

// Approach-1: Brute Force - O(n^3)
// Approch-2: Priority Queue (Max-Heap) + Segment Tree - O(k log(n^2) + n log n) -> O((n^2 + k) log n)
long long maxTotalValue(vector<int> &nums, int k) {
    int n = nums.size();

    SegmentTree minSegmentTree(nums, true);
    SegmentTree maxSegmentTree(nums, false);

    // Max-Heap to store the subarrays based on their values (max - min)
    priority_queue<tuple<ll, int, int>> pq; // Tuple format: (value, left index, right index)

    // Step-1: Initialize the heap with the best value for each starting index
    for(int l = 0; l < n; l++) {
        ll value = getValue(l, n - 1, minSegmentTree, maxSegmentTree, n);
        pq.push({value, l, n - 1});
    }

    // Step-2: Find the maximum value k times
    ll result = 0;

    while(k-- && !pq.empty()) {
        tuple<ll, int, int> current = pq.top();
        pq.pop();

        ll value = get<0>(current);
        int l = get<1>(current);
        int r = get<2>(current);

        result += value;

        if(r > l) {
            ll nextBestValue = getValue(l, r - 1, minSegmentTree, maxSegmentTree, n);
            pq.push(make_tuple(nextBestValue, l, r - 1));
        }
    }

    return result;
}

int main() {
    vector<int> nums = {4, 2, 5, 1};
    int k = 3;

    cout << maxTotalValue(nums, k) << endl;

    return 0;
}