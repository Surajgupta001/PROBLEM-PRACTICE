/*
New 21 Game - [Leetcode - 837(Medium)]
---------------------------------------
Alice plays the following game, loosely based on the card game "21".

Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets k or more points.

Return the probability that Alice has n or fewer points.

Answers within 10-5 of the actual answer are considered accepted.

Example 1:

Input: n = 10, k = 1, maxPts = 10
Output: 1.00000
Explanation: Alice gets a single card, then stops.

Example 2:

Input: n = 6, k = 1, maxPts = 10
Output: 0.60000
Explanation: Alice gets a single card, then stops.
In 6 out of 10 possibilities, she is at or below 6 points.

Example 3:

Input: n = 21, k = 17, maxPts = 10
Output: 0.73278

Constraints:

0 <= k <= n <= 104
1 <= maxPts <= 104
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

double new21Game(int n, int k, int maxPts){
    vector<double> prob(n + 1, 0.0);
    // prob[i] = probability of getting score = i
    prob[0] = 1.0;

    for (int i = 1; i <= n; i++){
        for (int card = 1; card <= maxPts; card++){
            if (i - card >= 0 && i - card < k){
                // probability of score card = 1/maxPts
                // Remaining score = p[i-card]
                prob[i] += prob[i - card] / maxPts;
            }
        }
    }

    // Sum probabilities for final scores in [k, n]
    return accumulate(prob.begin() + k, prob.begin() + n + 1, 0.0);
}

// Optimised code - Dynamic Programming
double new21Game(int n, int k, int maxPts){
    if (k == 0 || n >= k - 1 + maxPts) return 1.0;

    vector<double> prob(n + 1, 0.0);
    prob[0] = 1.0;

    double currProbabSum = 1.0; // sum of last maxPts prob[j] where j < k

    for (int i = 1; i <= n; ++i){
        prob[i] = currProbabSum / maxPts;

        if (i < k) {
            currProbabSum += prob[i];            // add new term while draws are allowed
        }
        // Always try to remove the (i - maxPts)-th term if it was part of the window and j < k
        if (i - maxPts >= 0 && i - maxPts < k) {
            currProbabSum -= prob[i - maxPts];
        }
    }
    return accumulate(prob.begin() + k, prob.begin() + n + 1, 0.0);
}

int main(){
    int n = 21, k = 17, maxPts = 10;
    double result = new21Game(n, k, maxPts);
    cout << "Probability: " << result << endl;
    return 0;
}