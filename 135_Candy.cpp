/*
Candy - [Leetcode - 135(Hard)]
-------------------------------
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104
*/

#include <iostream>
#include <vector>
using namespace std;

// Approach-1: Two-pass algorithm - O(n) time complexity and O(n) space complexity 
int candy(vector<int>& ratings) {
    int n = ratings.size();
    
    if (n == 0) return 0;

    vector<int> candies(n, 1); // Initialize candies array with 1 candy for each child

    // First pass: left to right
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1; // Give more candy than previous child
        }
    }

    // Second pass: right to left
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1); // Ensure current child has more than next child
        }
    }

    int totalCandies = 0;
    for (auto candy : candies) {
        totalCandies += candy; // Sum up all candies
    }

    return totalCandies;
}

// Approach-2: One-pass algorithm - O(n) time complexity and O(1) space complexity
int candy(vector<int>& ratings) {
    int n = ratings.size();
    int totalCandies = n; // Each child gets at least one candy

    int idx = 1;
    while (idx < n) {

        if (ratings[idx] == ratings[idx - 1]) {
            idx++;
            continue;
        }

        // For increasing slope
        int upSlope = 0;
        while (idx < n && ratings[idx] > ratings[idx - 1]) {
            upSlope++;
            totalCandies += upSlope;
            idx++;
            if (idx == n) return totalCandies;
        }

        // For decreasing slope
        int downSlope = 0;
        while (idx < n && ratings[idx] < ratings[idx - 1]) {
            downSlope++;
            totalCandies += downSlope;
            idx++;
        }

        // Remove the min candies from the peak (to avoid double counting)
        totalCandies -= min(upSlope, downSlope);
    }

    return totalCandies;
}

int main(){

    vector<int> ratings = {1, 0, 2};
    
    int result = candy(ratings);
    
    cout << "Minimum number of candies needed: " << result << endl;

    return 0;
}