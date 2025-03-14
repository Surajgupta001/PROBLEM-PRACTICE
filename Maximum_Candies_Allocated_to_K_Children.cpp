/*
Maximum Candies Allocated to K Children - [Leetcode - 2226(Medium)]
==================================================================
You are given a 0-indexed integer array candies. Each element in the array denotes a pile of candies of size candies[i]. You can divide each pile into any number of sub piles, but you cannot merge two piles together.

You are also given an integer k. You should allocate piles of candies to k children such that each child gets the same number of candies. Each child can be allocated candies from only one pile of candies and some piles of candies may go unused.

Return the maximum number of candies each child can get.


Example 1:

Input: candies = [5,8,6], k = 3
Output: 5
Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1. We now have five piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.

Example 2:

Input: candies = [2,5], k = 11
Output: 0
Explanation: There are 11 children but only 7 candies in total, so it is impossible to ensure each child receives at least one candy. Thus, each child gets no candy and the answer is 0.

Constraints:

1 <= candies.length <= 10^5
1 <= candies[i] <= 10^7
1 <= k <= 10^12
*/

#include <iostream>
#include <vector>
using namespace std;

// Check if it's possible to allocate candies so that each child gets 'x' candies
bool canAllocateCandies(vector<int> &candies, long long k, int x){ // x -> nummber Of Candies
    // Initialize the total number of children that can be served
    long long total = 0; // maximum Number OfChildren

    for (int i = 0; i < candies.size(); i++){
        total += candies[i] / x; // Add the number of children this pile can serve
    }
    return total >= k;
}

// Find the maximum number of candies each child can get
int maximumCandies(vector<int> &candies, long long k){
    // Find the maximum number of candies in any pile
    int max = 0; // maximum Candies In Pile
    for (int i = 0; i < candies.size(); i++){
        max = std::max(max, candies[i]);
    }

    // Set the initial search range for binary search
    int low = 0;
    int high = max;

    // Binary search to find the maximum number of candies each child can get
    while (low < high){
        // Calculate the middle value of the current range
        int mid = (low + high + 1) / 2;

        // Check if it's possible to allocate candies so that each child gets 'mid' candies
        if (canAllocateCandies(candies, k, mid)){
            // If possible, move to the upper half to search for a larger number
            low = mid;
        }
        else{
            // Otherwise, move to the lower half
            high = mid - 1;
        }
    }
    return low;
}


int main(){
    int n, k;
    cin >> n >> k;
    vector<int> candies(n);
    for (int i = 0; i < n; i++){
        cin >> candies[i];
    }
    cout << maximumCandies(candies, k) << endl;
}