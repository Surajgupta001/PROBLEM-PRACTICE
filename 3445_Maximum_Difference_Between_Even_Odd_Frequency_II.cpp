/*
Maximum Difference Between Even and Odd Frequency II - [Leetcode - 3445(Hard)]
-------------------------------------------------------------------------------
You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:

subs has a size of at least k.
Character a has an odd frequency in subs.
Character b has an even frequency in subs.
Return the maximum difference.

Note that subs can contain more than 2 distinct characters.



Example 1:

Input: s = "12233", k = 4

Output: -1

Explanation:

For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.

Example 2:

Input: s = "1122211", k = 3

Output: 1

Explanation:

For the substring "11222", the frequency of '2' is 3 and the frequency of '1' is 2. The difference is 3 - 2 = 1.

Example 3:

Input: s = "110", k = 3

Output: -1



Constraints:

3 <= s.length <= 3 * 104
s consists only of digits '0' to '4'.
The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
1 <= k <= s.length
*/

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int getState(int count_a, int count_b){
    int parity_a = count_a % 2; // odd : parity will be 1 , even : parity will be 0
    int parity_b = count_b % 2;

    if (parity_a == 0 && parity_b == 0) return 0; // even even (00)
    if (parity_a == 0 && parity_b == 1) return 1; // even odd (01)
    if (parity_a == 1 && parity_b == 0) return 2; // odd even (10)

    return 3; // odd odd (11)
}

int maxDifference(string s, int k){
    int n = s.length();

    int result = INT_MIN;

    // Step-1 Try all possible pairs a and b from ('0' to '4') where a != b
    for (char a = '0'; a <= '4'; a++){
        for (char b = '0'; b <= '4'; b++){
            if (a == b) continue;

            // stateMinPrev_a_b[state] = stores the smallest value of count of a - count of b
            vector<int> stateMinPrev_a_b(4, INT_MAX);

            // Count of a and count of b till index r
            int count_a = 0;
            int count_b = 0;

            // Count of a and count of b till prev index l
            int prev_a = 0;
            int prev_b = 0;

            // Let's start the sliding window
            int l = -1;
            int r = 0;

            while (r < n){
                count_a += (s[r] == a) ? 1 : 0;
                count_b += (s[r] == b) ? 1 : 0;

                // Now try to shrink from l
                while (r - l >= k && count_b - prev_b >= 2 && count_a - prev_a >= 1){
                    int leftState = getState(prev_a, prev_b);
                    stateMinPrev_a_b[leftState] = min(stateMinPrev_a_b[leftState], prev_a - prev_b);

                    l++;
                    prev_a += (s[l] == a) ? 1 : 0;
                    prev_b += (s[l] == b) ? 1 : 0;
                }

                int rightState = getState(count_a, count_b);
                int bestLeftState = rightState ^ 2;
                int bestMinDiffValueLeft = stateMinPrev_a_b[bestLeftState];

                if (bestMinDiffValueLeft != INT_MAX){
                    result = max(result, (count_a - count_b) - bestMinDiffValueLeft);
                }

                r++;
            }
        }
    }

    return result;
}

int main () {
    string s;
    int k;

    cout << "Enter the string (s): ";
    cin >> s;
    cout << "Enter the integer (k): ";
    cin >> k;

    int result = maxDifference(s, k);
    
    if (result == INT_MIN) {
        cout << "No valid substring found." << endl;
    }
    else {
        cout << "Maximum difference: " << result << endl;
    }

    return 0;
}