/*
Find All People With Secret - [Leetcode - 2092(Hard)]
------------------------------------------------------
You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.

Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.

The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.

Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.

Example 1:

Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
Output: [0,1,2,3,5]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 5, person 1 shares the secret with person 2.
At time 8, person 2 shares the secret with person 3.
At time 10, person 1 shares the secret with person 5.​​​​
Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.

Example 2:

Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
Output: [0,1,3]
Explanation:
At time 0, person 0 shares the secret with person 3.
At time 2, neither person 1 nor person 2 know the secret.
At time 3, person 3 shares the secret with person 0 and person 1.
Thus, people 0, 1, and 3 know the secret after all the meetings.

Example 3:

Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
Output: [0,1,2,3,4]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
Note that person 2 can share the secret at the same time as receiving it.
At time 2, person 3 shares the secret with person 4.
Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.
 

Constraints:

2 <= n <= 10^5
1 <= meetings.length <= 10^5
meetings[i].length == 3
0 <= xi, yi <= n - 1
xi != yi
1 <= timei <= 10^5
1 <= firstPerson <= n - 1
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

//Approach-1 (Most basic approach that can come to mind)
//T.C : ~O(M*(M+N)) where M = number of meetings and N = number of people
//S.C : O(M+N)
vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    map<int, vector<pair<int, int>>> timeMeetings;
    
    for(vector<int>& meeting : meetings) {
        int person1 = meeting[0];
        int person2 = meeting[1];
        int time    = meeting[2];
        
        timeMeetings[time].push_back({person1, person2});
    }
    
    vector<bool> knowsSecret(n, false);
    knowsSecret[0] = true;
    knowsSecret[firstPerson] = true;
    
    //Solve in increasing time meetings
    for(auto &itr : timeMeetings) {
        
        int t = itr.first;
        vector<pair<int, int>> meets = itr.second;
        
        unordered_map<int, vector<int>> graph;
        
        queue<int> qu;
        unordered_set<int> alreadyAdded;
        
        for(auto& [person1, person2] : meets) {
            graph[person1].push_back(person2);
            graph[person2].push_back(person1);
            
            if(knowsSecret[person1] && alreadyAdded.find(person1) == alreadyAdded.end()) {
                qu.push(person1);
                alreadyAdded.insert(person1);
            }

            if(knowsSecret[person2] && alreadyAdded.find(person2) == alreadyAdded.end()) {
                qu.push(person2);
                alreadyAdded.insert(person2);
            }
        }
            
        //Now I know who meet who based on increasing time
        //Let's hit the BFS to spread the secret
        
        while(!qu.empty()) {
            int person = qu.front();
            qu.pop();
            
            for(auto &nextPerson : graph[person]) {
                if(!knowsSecret[nextPerson]) {
                    knowsSecret[nextPerson] = true;
                    qu.push(nextPerson);
                }
            }
        }
    }
    
    vector<int> result;
    for(int i = 0; i < n; i++) {
        if(knowsSecret[i] == true) {
            result.push_back(i);
        }
    }
    
    return result;
}

//Approach-2 (Using BFS Graph Traversal)
//T.C : O(M * (M+N)) -> M = Number of meetings, N = Number of people, there can be at most N+M elements in the queue and a person may have M neighbours
//S.C : O(M+N)
vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    unordered_map<int, vector<pair<int, int>>> graph;
    
    for(vector<int>& meeting : meetings) {
        int person1 = meeting[0];
        int person2 = meeting[1];
        int time    = meeting[2];
        
        graph[person1].push_back({person2, time});
        graph[person2].push_back({person1, time});
    }
    
    queue<pair<int, int>> qu;
    qu.push({0, 0});
    qu.push({firstPerson, 0});
    
    vector<int> earlySecretTime(n, INT_MAX);
    earlySecretTime[0] = 0;
    earlySecretTime[firstPerson] = 0;
    
    while(!qu.empty()) {
        auto [person, time] = qu.front();
        
        qu.pop();
        
        for(auto& neighbour : graph[person]) {
            int nextPerson = neighbour.first;
            int t = neighbour.second;
            
            if(t >= time && earlySecretTime[nextPerson] > t) {
                earlySecretTime[nextPerson] = t;
                qu.push({nextPerson, t});
            }
        }
    }
    
    vector<int> result;
    for(int i = 0; i < n; i++) {
        if(earlySecretTime[i] != INT_MAX) {
            result.push_back(i);
        }
    }
    
    return result;
}


//Approach-3 (Using DFS Graph Traversal)
//T.C : O(M * (M+N)) -> M = Number of meetings, N = Number of people (Although it's a DFS, but we also revisit some nodes again with better secret knowing time)
//S.C : O(M+N)

void dfs(int person, int time, unordered_map<int, vector<pair<int, int>>>& graph, vector<int>& earlySecretTime) {
    for(auto& neighbour : graph[person]) {
        int nextPerson = neighbour.first;
        int t = neighbour.second;
        
        if(t >= time && earlySecretTime[nextPerson] > t) {
            earlySecretTime[nextPerson] = t;
            dfs(nextPerson, t, graph, earlySecretTime);
        }
    }
}

vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    unordered_map<int, vector<pair<int, int>>> graph;
    
    for(vector<int>& meeting : meetings) {
        int person1 = meeting[0];
        int person2 = meeting[1];
        int time    = meeting[2];
        
        graph[person1].push_back({person2, time});
        graph[person2].push_back({person1, time});
    }
    
    vector<int> earlySecretTime(n, INT_MAX);
    earlySecretTime[0] = 0;
    earlySecretTime[firstPerson] = 0;
    
    // Do DFS
    dfs(0, 0, graph, earlySecretTime);
    dfs(firstPerson, 0, graph, earlySecretTime);
    
    vector<int> result;
    
    for(int i = 0; i < n; i++) {
        if(earlySecretTime[i] != INT_MAX) {
            result.push_back(i);
        }
    }
    
    return result;
}


//Approach-4 (Using min-heap to fetch earliest time)
//T.C : ~O((N+M) * (log(M+N) + M)) 
//S.C : O(N+M)
vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    unordered_map<int, vector<pair<int, int>>> graph;
    
    for(vector<int>& meeting : meetings) {
        int person1 = meeting[0];
        int person2 = meeting[1];
        int time    = meeting[2];
        
        graph[person1].push_back({person2, time});
        graph[person2].push_back({person1, time});
    }
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //I need the ones first having min time
    pq.push({0, 0});
    pq.push({0, firstPerson});
    
    vector<bool> visited(n, false);
    
    while(!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        
        int time = top.first;
        int person = top.second;
        
        if(visited[person] == true) {
            continue;
        }
        visited[person] = true;
        
        for(auto& neighbour : graph[person]) {
            int nextPerson = neighbour.first;
            int t          = neighbour.second;
            
            if(t >= time && !visited[nextPerson]) {
                pq.push({t, nextPerson});
            }
        }
    }
    
    vector<int> result;
    for(int i = 0; i < n; i++) {
        if(visited[i] == true) {
            result.push_back(i);
        }
    }
    
    return result;
}

int main() {
    // Example usage:
    int n = 6;
    vector<vector<int>> meetings = {{1,2,5},{2,3,8},{1,5,10}};
    int firstPerson = 1;

    // You can test any approach by uncommenting the desired function call:
    vector<int> result = findAllPeople(n, meetings, firstPerson);

    cout << "People with the secret: ";
    for (int person : result) {
        cout << person << " ";
    }
    cout << endl;

    return 0;
}