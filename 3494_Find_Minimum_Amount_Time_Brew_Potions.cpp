/*
Find the Minimum Amount of Time to Brew Potions - [Leetcode - 3494(Medium)]
----------------------------------------------------------------------------
You are given two integer arrays, skill and mana, of length n and m, respectively.

In a laboratory, n wizards must brew m potions in order. Each potion has a mana capacity mana[j] and must pass through all the wizards sequentially to be brewed properly. The time taken by the ith wizard on the jth potion is timeij = skill[i] * mana[j].

Since the brewing process is delicate, a potion must be passed to the next wizard immediately after the current wizard completes their work. This means the timing must be synchronized so that each wizard begins working on a potion exactly when it arrives. ​

Return the minimum amount of time required for the potions to be brewed properly.

Example 1:

Input: skill = [1,5,2,4], mana = [5,1,4,2]

Output: 110

Explanation:

Potion Number	Start time	Wizard 0 done by	Wizard 1 done by	Wizard 2 done by	Wizard 3 done by
0	0	5	30	40	60
1	52	53	58	60	64
2	54	58	78	86	102
3	86	88	98	102	110
As an example for why wizard 0 cannot start working on the 1st potion before time t = 52, consider the case where the wizards started preparing the 1st potion at time t = 50. At time t = 58, wizard 2 is done with the 1st potion, but wizard 3 will still be working on the 0th potion till time t = 60.

Example 2:

Input: skill = [1,1,1], mana = [1,1,1]

Output: 5

Explanation:

Preparation of the 0th potion begins at time t = 0, and is completed by time t = 3.
Preparation of the 1st potion begins at time t = 1, and is completed by time t = 4.
Preparation of the 2nd potion begins at time t = 2, and is completed by time t = 5.
Example 3:

Input: skill = [1,2,3,4], mana = [1,2]

Output: 21

Constraints:

n == skill.length
m == mana.length
1 <= n, m <= 5000
1 <= mana[i], skill[i] <= 5000
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach: Simulation Based Problems
// Time Complexity: O(n*m)
// Space Complexity: O(n)
long long minTime(vector<int>& skill, vector<int>& mana) {
    int n = skill.size();
    int m = mana.size();

    // finishTime[i] is the time when wizard i finishes brewing the current potion
    vector<long long> finishTime(n, 0);

    for(int j=0; j<m; j++){
        // Wizard 0 starts brewing the j-th potion as soon as they finish the previous one
        finishTime[0] = finishTime[0] + (long long)skill[0] * mana[j];

        for(int i=1; i<n; i++){
            // Each subsequent wizard starts brewing the j-th potion after they finish the previous one and after the previous wizard finishes brewing the j-th potion
            finishTime[i] = max(finishTime[i], finishTime[i-1]) + (long long)skill[i] * mana[j];
        }

        // Synchronize the finish times of wizards after each potion
        for(int i=n-1; i>0; i--){
            // Update finishTime of wizard i-1 to reflect the time they finished brewing the j-th potion
            finishTime[i-1] = finishTime[i] - (long long)skill[i] * mana[j];
        }

    }
    return finishTime[n-1]; // The total time taken is when the last wizard finishes brewing the last potion
}

int main() {
    vector<int> skill = {1, 5, 2, 4};
    vector<int> mana = {5, 1, 4, 2};
    
    long long result = minTime(skill, mana);
    cout << "Minimum amount of time to brew potions: " << result << endl; // Output: 110
    
    return 0;
}