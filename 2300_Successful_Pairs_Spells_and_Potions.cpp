/*
Successful Pairs of Spells and Potions - [Leetcode - 2300(Medium)]
--------------------------------------------------------------------
You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.

You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.

Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.

Example 1:

Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Example 2:

Input: spells = [3,1,2], potions = [8,5,8], success = 16
Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful. 
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful. 
Thus, [2,0,2] is returned.
 

Constraints:

n == spells.length
m == potions.length
1 <= n, m <= 105
1 <= spells[i], potions[i] <= 105
1 <= success <= 1010
*/ 

/*
=> The ceil function in C++ is a mathematical function that returns the smallest integer value greater than or equal to the given double argument.
=> It is part of the C++ standard library and uses the __cdecl calling convention.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Approach - 1 : Brute Force (TLE)
// Time Complexity : O(n*m)
// Space Complexity : O(1)
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success){
    int m = spells.size();
    int n = potions.size();
    vector<int> ans(m, 0);
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            long long prod = (long long)spells[i] * (long long)potions[j];
            if(prod >= success) {
                ans[i]++;
            }
        }
    }
    return ans;
}

// Approach - 2 : Binary Search -> Lower Bound
// Time Complexity : O(nlogm)
// Space Complexity : O(1)
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success){
    int m = spells.size();
    int n = potions.size();
    
    sort(potions.begin(), potions.end());

    int maxPositionalValue = potions[n-1];
    
    vector<int> ans;
    
    for(int i=0; i<m; i++){
        int spell = spells[i];
        // minPotion * spell >= success
        long long minPotion = ceil((double(success) / double(spell)));

        if(minPotion > maxPositionalValue){
            ans.push_back(0);
            continue;
        }

        int idx = lower_bound(potions.begin(), potions.end(), minPotion) - potions.begin(); // portion >= minPotion
        ans.push_back(n - idx);
    }
    return ans;
}

// Approach - 3 : Binary Search -> Custom Implementation
// Time Complexity : O(nlogm)
// Space Complexity : O(1)
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success){
    int m = spells.size();
    int n = potions.size();
    
    sort(potions.begin(), potions.end());

    int maxPositionalValue = potions[n-1];
    
    vector<int> ans;
    
    for(int i=0; i<m; i++){
        int spell = spells[i];
        // minPotion * spell >= success
        long long minPotion = ceil((double(success) / double(spell)));

        if(minPotion > maxPositionalValue){
            ans.push_back(0);
            continue;
        }

        // Custom Binary Search Implementation
        int low = 0;
        int high = n - 1;
        
        int idx = n; // Default value if no potion found

        while(low <= high){
            int mid = low + (high - low) / 2;

            if(potions[mid] >= minPotion){
                idx = mid; // Potential answer found
                high = mid - 1; // Look for a smaller index
            } 
            else {
                low = mid + 1; // Look in the high half
            }
        }

        ans.push_back(n - idx);
    }
    return ans;
}

int main() {
    vector<int> spells = {5,1,3};
    vector<int> potions = {1,2,3,4,5};
    long long success = 7;
    vector<int> ans = successfulPairs(spells, potions, success);
    for(auto x: ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}