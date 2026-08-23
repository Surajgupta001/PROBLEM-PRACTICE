/*
Sum Game - [Leetcode - 1927(Medium)]
--------------------------------------
Alice and Bob take turns playing a game, with Alice starting first.

You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:

Choose an index i where num[i] == '?'.
Replace num[i] with any digit between '0' and '9'.
The game ends when there are no more '?' characters in num.

For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.

For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win. 

Example 1:

Input: num = "5023"
Output: false
Explanation: There are no moves to be made.
The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.

Example 2:

Input: num = "25??"
Output: true
Explanation: Alice can replace one of the '?'s with '9' and it will be impossible for Bob to make the sums equal.

Example 3:

Input: num = "?3295???"
Output: false
Explanation: It can be proven that Bob will always win. One possible outcome is:
- Alice replaces the first '?' with '9'. num = "93295???".
- Bob replaces one of the '?' in the right half with '9'. num = "932959??".
- Alice replaces one of the '?' in the right half with '2'. num = "9329592?".
- Bob replaces the last '?' in the right half with '7'. num = "93295927".
Bob wins because 9 + 3 + 2 + 9 = 5 + 9 + 2 + 7.

Constraints:

2 <= num.length <= 10^5
num.length is even.
num consists of only digits and '?'.
*/

#include <iostream>
#include <string>
using namespace std;

bool sumGame(string num) {
    int n = num.length();
    
    int leftKnownSum = 0;
    int rightKnownSum = 0;

    int LeftQnMarkCount = 0;
    int RightQnMarkCount = 0;

    for(int i = 0; i < n; i++){
        if(num[i] == '?'){
            if(i < n/2){ // left half
                LeftQnMarkCount++;
            } else { // right half
                RightQnMarkCount++;
            }
        } else {
            if(i < n/2){ // left half
                leftKnownSum += (num[i] - '0');
            } else { // right half
                rightKnownSum += (num[i] - '0');
            }
        }
    }

    int totalQnMarkCount = LeftQnMarkCount + RightQnMarkCount;

    if(totalQnMarkCount % 2 == 1){ // Odd - Alice always wins
        return true;
    } else { // Even - Check if Alice can make the sums unequal
        int LEFT = 2 * leftKnownSum + 9 * LeftQnMarkCount;
        int RIGHT = 2 * rightKnownSum + 9 * RightQnMarkCount;

        if(LEFT == RIGHT){ // Bob wins
            return false;
        } else { // Alice wins
            return true;
        }
    }
}

int main() {
    string num = "25??";
    
    bool result = sumGame(num);
    cout << (result ? "true" : "false") << endl;
    
    return 0;
}