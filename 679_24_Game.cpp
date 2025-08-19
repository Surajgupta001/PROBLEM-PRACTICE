/*
24 Game - [Leetcode - 679(Hard)]
---------------------------------
You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.

You are restricted with the following rules:

The division operator '/' represents real division, not integer division.
For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
You cannot concatenate numbers together
For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
Return true if you can get such expression that evaluates to 24, and false otherwise.

Example 1:

Input: cards = [4,1,8,7]
Output: true
Explanation: (8-4) * (7-1) = 24

Example 2:

Input: cards = [1,2,1,2]
Output: false


Constraints:

cards.length == 4
1 <= cards[i] <= 9

*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double epsilon = 1e-6; // 0.01, 0.001 etc will work too.
// Tolerance for floating-point comparison. To avoid floating point precission errors

bool solve(vector<double> &cards){
    if(cards.size() == 1){
        return abs(cards[0] - 24) <= epsilon;
    }

    // pick two possible numbers
    for(int i = 0; i < cards.size(); i++){
        for(int j = 0; j < cards.size(); j++){
            if(i == j) continue;

            vector<double> tempCards;
            for(int k = 0; k < cards.size(); k++){
                if (k != i && k != j){
                    tempCards.push_back(cards[k]);
                }
            }

            double a = cards[i];
            double b = cards[j];
            vector<double> possibleValues = {a + b, a - b, b - a, a * b}; // b-a is not required, our i and j for loop will take care of it

            if(abs(b) > 0.0) possibleValues.push_back(a / b);

            if(abs(a) > 0.0) possibleValues.push_back(b / a); // b/a is not required, our i and j for loop will take care of it

            for(double value : possibleValues){
                tempCards.push_back(value);     // Do
                if (solve(tempCards) == true) return true; // Explore
                tempCards.pop_back(); // Pop/Undo --> BACKTRACKING STEPS
            }
        }
    }

    return false;
}

bool judgePoint24(vector<int> &cards){
    vector<double> nums;
    for (int i = 0; i < cards.size(); i++){
        nums.push_back(1.0 * cards[i]);
    }
    return solve(nums);
}

int main(){
    vector<int> cards1 = {4, 1, 8, 7};
    vector<int> cards2 = {1, 2, 1, 2};

    cout << (judgePoint24(cards1) ? "true" : "false") << endl;
    cout << (judgePoint24(cards2) ? "true" : "false") << endl;

    return 0;
}