/*
Distribute Candies Among Children II - [Leetcode - 2929(Medium)]
-----------------------------------------------------------------
You are given two positive integers n and limit.

Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.

Example 1:

Input: n = 5, limit = 2
Output: 3
Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).

Example 2:

Input: n = 3, limit = 3
Output: 10
Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies: (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).
 

Constraints:

1 <= n <= 106
1 <= limit <= 106
*/ 

#include <iostream>
using namespace std;

// Brute Force Approach
long long distributeCandies(int n, int limit) {
    long long count = 0;
    for (int i = 0; i <= min(n, limit); ++i) { // i represents candies given to first child
        for (int j = 0; j <= min(n-1, limit); ++j) { // j represents candies given to second child
            int k = n - (i + j); // k represents candies given to third child
            if (k >= 0 && k <= limit) { // Check if third child gets valid candies
                count++; // Increment count for valid distribution
            }
        }
    }
    return count;
}

// Recursive Approach
long long helper(int countChild, int n, int limit){
    if(countChild == 3) {
        return n == 0 ? 1 : 0; // If all children are considered, check if candies are exhausted
    }

    int ways = 0;
    for(int i = 0; i <= min(n, limit); ++i) { // Iterate through possible candies for current child
        ways += helper(countChild + 1, n - i, limit); // Recur for next child with remaining candies
    }
    return ways; // Return total ways for current distribution
}

long long distributeCandies(int n, int limit){
    return helper(0, n, limit); // Start recursion with first child
}

// Efficeint Approach
long long distributeCandiesEfficient(int n, int limit) {
    long long ways = 0;

    // Child 1
    int minChid1 = max(0, n-2*limit);
    int maxChild1 = min(n, limit);

    for(int i=minChid1; i<= maxChild1; i++){ // Fixing child assignment of candies
        int N = n - i; // For child2 and child3
        
        int minChild2 = max(0, N-limit);
        int maxChild2 = min(N, limit);

        ways += maxChild2 - minChild2 + 1;
    }

    return ways;
}
    

int main() {

    int n, limit;
    cout << "Enter the number of candies (n): ";
    cin >> n;
    cout << "Enter the limit for each child: ";
    cin >> limit;

    long long result = distributeCandies(n, limit);
    cout << "Total number of ways to distribute candies: " << result << endl;

    return 0;
}