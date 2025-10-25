/*
Calculate Money in Leetcode Bank - [Leetcode - 1716(Easy)]
-----------------------------------------------------------
Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.

He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday.

Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.

Example 1:

Input: n = 4
Output: 10
Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.
Example 2:

Input: n = 10
Output: 37
Explanation: After the 10th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4) = 37. Notice that on the 2nd Monday, Hercy only puts in $2.
Example 3:

Input: n = 20
Output: 96
Explanation: After the 20th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4 + 5 + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96.

Constraints:

1 <= n <= 1000
*/

#include <iostream>
using namespace std;

//Approach-1 (Simple simulation)
//T.C : O(1) - see the video above to know why
//S.C : O(1)
int totalMoney(int n) {
    int result = 0;
    int monday_money = 1; //1dollar
    
    while(n > 0) {
        int money = monday_money; //1
        
        for(int day = 1; day <= min(n, 7); day++) {
            result += money;
            money++;
        }

        n -= 7;
        monday_money++;
    }
    
    return result;
}



//Approach-2 (Using AP and a for loop)
//T.C : O(1) - see the video above to know why
//S.C : O(1)
int totalMoney(int n) {
    int terms = n/7; //Weeks
    int first = 28;
    int last  = 28 + (terms - 1) * 7; //AP formula for n-th term
    
    int result = terms * (first + last) / 2; //Sum of nth terms in an AP
    
    //Final week remaining days = n%7
    int start_money = 1 + terms;
    
    for(int day = 1; day <= (n%7); day++) {
        result += start_money;
        start_money++;
    }
    
    return result;
}



//Approach-3 (Using AP completely)
//T.C : O(1) - see the video above to know why
//S.C : O(1)
int totalMoney(int n) {
    int terms = n/7; //Weeks
    int first = 28;
    int last  = 28 + (terms - 1) * 7; //AP formula for n-th term
    
    int result = terms * (first + last) / 2; //Sum of nth terms in an AP
    
    //remaining days
    int remain = n%7;
    int first_term = (1 + terms);
    int last_term  = first_term + remain - 1;
    
    result += remain * (first_term + last_term) / 2;
    
    return result;
}

int main() {
    int n = 20;
    cout << totalMoney(n) << endl;
    return 0;
}