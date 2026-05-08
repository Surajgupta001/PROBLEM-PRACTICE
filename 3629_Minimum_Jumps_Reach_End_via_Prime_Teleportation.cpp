/*
Minimum Jumps to Reach End via Prime Teleportation - [Leetcode - 3629(Medium)]
[----------------------------------------------------------------------------------
You are given an integer array nums of length n.

You start at index 0, and your goal is to reach index n - 1.

From any index i, you may perform one of the following operations:

Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
Return the minimum number of jumps required to reach index n - 1.

Example 1:

Input: nums = [1,2,4,6]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index 1.
At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
Thus, the answer is 2.

Example 2:

Input: nums = [2,3,4,7,9]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index i = 1.
At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
Thus, the answer is 2.

Example 3:

Input: nums = [4,6,5,8]

Output: 3

Explanation:

Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

Constraints:

1 <= n == nums.length <= 10^5
1 <= nums[i] <= 10^6]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

void SieveOfEratosthenes(int maxElement, vector<bool>& isPrime) {
    isPrime.resize(maxElement + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers

    for (int num = 2; num * num <= maxElement; num++) {
        if (isPrime[num]) {
            for (int multiple = num * num; multiple <= maxElement; multiple += num) {
                isPrime[multiple] = false;
            }
        }
    }
}

int minJumps(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, vector<int>> map; // element -> indices
    int maxElement = 0;

    for(int i=0; i<n; i++){ // O(n)
        map[nums[i]].push_back(i);
        maxElement = max(maxElement, nums[i]);
    }

    // Build isPrime vector using Sieve of Eratosthenes
    vector<bool> isPrime;
    SieveOfEratosthenes(maxElement, isPrime); // O(maxElement ** log log maxElement)

    // BFS
    queue<int> qu;
    vector<bool> visited(n, false);
    qu.push(0);
    visited[0] = true;

    unordered_set<int> visitedPrimes; // To avoid teleporting multiple times from the same prime

    int steps = 0;

    // We visit each node only once - O(n)
    // Overall time complexity: O(n + maxElement ** log log maxElement)
    // Overall space complexity: O(n + maxElement)
    while(not qu.empty()){
        int size = qu.size();

        while(size--){
            int i = qu.front();
            qu.pop();

            if(i == n-1) return steps;

            if(i-1 >= 0 and not visited[i-1]){
                qu.push(i-1);
                visited[i-1] = true;
            }

            if(i+1 < n and not visited[i+1]){
                qu.push(i+1);
                visited[i+1] = true;
            }

            if (!isPrime[nums[i]] || visitedPrimes.count(nums[i])) {
                continue; // Not a prime or already teleported from this prime
            }

            for(int multiple=nums[i]; multiple <= maxElement; multiple += nums[i]){
                if(not map.count(multiple)) continue; // No indices with this multiple

                for(auto j : map[multiple]){
                    if(j != i and not visited[j]){
                        qu.push(j);
                        visited[j] = true;
                    }
                }
            }

            visitedPrimes.insert(nums[i]); // Mark this prime as visited for teleportation
        }

        steps++;
    }

    return steps;
}

int main() {
    vector<int> nums1 = {1, 2, 4, 6};
    cout << minJumps(nums1) << endl; // Output: 2

    vector<int> nums2 = {2, 3, 4, 7, 9};
    cout << minJumps(nums2) << endl; // Output: 2

    vector<int> nums3 = {4, 6, 5, 8};
    cout << minJumps(nums3) << endl; // Output: 3

    return 0;
}