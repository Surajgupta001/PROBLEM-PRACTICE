/*
Rearranging Fruits - [Leetcode - 2561(HARD)]
---------------------------------------------
You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:

Chose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
The cost of the swap is min(basket1[i],basket2[j]).
Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

Return the minimum cost to make both the baskets equal or -1 if impossible.

Example 1:

Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
Output: 1
Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.

Example 2:

Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
Output: -1
Explanation: It can be shown that it is impossible to make both the baskets equal.
 

Constraints:

basket1.length == basket2.length
1 <= basket1.length <= 105
1 <= basket1[i],basket2[i] <= 109

*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

long long minCost(vector<int> &basket1, vector<int> &basket2){
    unordered_map<int, int> mp;
    int minElement = INT_MAX;

    for (int &x : basket1){
        mp[x]++; // Count frequency of each fruit in basket1
        minElement = min(minElement, x);
    }

    for (int &x : basket2){
        mp[x]--; // Taki remaining extra pata chal jaye
        minElement = min(minElement, x);
    }

    vector<int> extraFruits;
    for (auto &it : mp){
        int cost = it.first;
        int count = it.second;

        if (count == 0) continue; // If count is zero, no need to do anything

        if (count % 2 != 0) return -1; // If count is odd, we cannot make the baskets equal

        for (int c = 1; c <= abs(count) / 2; c++){
            extraFruits.push_back(cost);
        }
    }

    // sort(begin(extraFruits), end(extraFruits)); // we need half elements only, so no need to complete sort

    // Instead, we can use partial sort
    nth_element(begin(extraFruits), begin(extraFruits) + extraFruits.size() / 2, end(extraFruits));

    long long totalCost = 0;
    for (int i = 0; i < extraFruits.size() / 2; i++){
        totalCost += min(extraFruits[i], minElement * 2);
    }

    return totalCost;
}

int main() {
    
    vector<int> basket1 = {4, 2, 2, 2};
    vector<int> basket2 = {1, 4, 1, 2};
    
    long long result = minCost(basket1, basket2);
    
    cout << result << endl;
}