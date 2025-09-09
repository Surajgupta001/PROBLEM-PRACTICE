/*
Number of People Aware of a Secret - [Leetcode - 2327(Medium)]
---------------------------------------------------------------
On day 1, one person discovers a secret.

You are given an integer delay, which means that each person will share the secret with a new person every day, starting from delay days after discovering the secret. You are also given an integer forget, which means that each person will forget the secret forget days after discovering it. A person cannot share the secret on the same day they forgot it, or on any day afterwards.

Given an integer n, return the number of people who know the secret at the end of day n. Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: n = 6, delay = 2, forget = 4
Output: 5
Explanation:
Day 1: Suppose the first person is named A. (1 person)
Day 2: A is the only person who knows the secret. (1 person)
Day 3: A shares the secret with a new person, B. (2 people)
Day 4: A shares the secret with a new person, C. (3 people)
Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
Day 6: B shares the secret with E, and C shares the secret with F. (5 people)
Example 2:

Input: n = 4, delay = 1, forget = 3
Output: 6
Explanation:
Day 1: The first person is named A. (1 person)
Day 2: A shares the secret with B. (2 people)
Day 3: A and B share the secret with 2 new people, C and D. (4 people)
Day 4: A forgets the secret. B, C, and D share the secret with 3 new people. (6 people)
 

Constraints:

2 <= n <= 1000
1 <= delay < forget <= n
*/ 

#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9 + 7;

// ========= Recursion + Memoization ==========
// This will return total number of people who know secret on day "day"
int solve(int day, int delay, int forget, vector<int>& dp) {
    if (day == 1) return 1;
    if (dp[day] != -1) return dp[day];

    int result = 0;
    for (int prevDay = day - forget + 1; prevDay <= day - delay; prevDay++) {
        if (prevDay > 0) {
            result = (result + solve(prevDay, delay, forget, dp)) % mod;
        }
    }
    return dp[day] = result;
}

int peopleAwareOfSecret(int n, int delay, int forget) {
    vector<int> dp(n + 1, -1);
    int total = 0;

    for (int day = n - forget + 1; day <= n; day++) {
        if (day > 0) {
            total = (total + solve(day, delay, forget, dp)) % mod;
        }
    }
    return total;
}

// ======== Tabulation ==========
int peopleAwareOfSecret(int n, int delay, int forget){
    vector<int> dp(n + 1);
    dp[1] = 1;
    
    /*
    for(int day = 2; day <= n; day++){
        long long count = 0;
        for(int prevDay = day - forget + 1; prevDay <= day - delay; prevDay++){
            if(prevDay > 0){
                count = (count + dp[prevDay]) % mod;
            }
        }
        dp[day] = count;
    }
    */ 

    // Slightly Optimized Tabulation => much better efficiency 100%
    int count = 0; // Window sum of range [day-forget+1 to day-delay]
    for(int day = 2; day <= n; day++){
        if(day-delay > 0){
            count = (count + dp[day-delay]) % mod;
        }

        if(day-forget > 0){
            count = (count - dp[day-forget] + mod) % mod;
        }

        dp[day] = count;
    }

    long long result = 0;
    
    for(int day = n - forget + 1; day <= n; day++){
        result = (result + dp[day]) % mod;
    }
    return result;
}

int main() {
    
    int n = 6, delay = 2, forget = 4;
    
    cout << peopleAwareOfSecret(n, delay, forget) << endl; // Output: 5
    
    return 0;
}