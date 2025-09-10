/*
Minimum Number of People to Teach - [Leetcode - 1733(Medium)]
--------------------------------------------------------------
On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.

You are given an integer n, an array languages, and an array friendships where:

There are n languages numbered 1 through n,
languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.
You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.

Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.

Example 1:

Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
Output: 1
Explanation: You can either teach user 1 the second language or user 2 the first language.
Example 2:

Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
Output: 2
Explanation: Teach the third language to users 1 and 3, yielding two users to teach.

Constraints:

2 <= n <= 500
languages.length == m
1 <= m <= 500
1 <= languages[i].length <= n
1 <= languages[i][j] <= n
1 <= u​​​​​​i < v​​​​​​i <= languages.length
1 <= friendships.length <= 500
All tuples (u​​​​​i, v​​​​​​i) are unique
languages[i] contains only unique values
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
    set<int> sadUsers; // Set to store users who cannot communicate with their friends
    
    // Check each friendship
    for(auto &friends : friendships){
        int u = friends[0] - 1; // convert this to 0-based indexing
        int v = friends[1] - 1; // convert this to 0-based indexing

        set<int> languageSet(languages[u].begin(), languages[u].end()); // insert all languages of user u in a set

        bool canTalk = false;
        // Check if user v knows any language that user u knows
        for(auto &lang : languages[v]){
            if(languageSet.find(lang) != languageSet.end()){
                canTalk = true;
                break;
            }
        }
        // If they cannot communicate, add both users to sadUsers set
        if(!canTalk){
            sadUsers.insert(u);
            sadUsers.insert(v);
        }
    }
    
    // Find the language known by the most sad users
    vector<int> languageCount(n + 1, 0); // languageCount[i] = number of sad users who know language i
    int mostKnownLanguage = 0;

    // Count languages among sad users
    for(auto &user : sadUsers){
        for(auto &lang : languages[user]){
            languageCount[lang]++;
            mostKnownLanguage = max(mostKnownLanguage, languageCount[lang]);
        }
    }
    // The answer is the number of sad users minus the number who already know the most common language
    return sadUsers.size() - mostKnownLanguage;
}

int main(){
    int n = 2;
    vector<vector<int>> languages = {{1},{2},{1,2}};
    vector<vector<int>> friendships = {{1,2},{1,3},{2,3}};
    cout << minimumTeachings(n, languages, friendships) << endl;
    return 0;
}