/*
Keys and Rooms - [LeetCode - 841(Medium)]
------------------------------------------
There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.

Example 1:

Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.

Example 2:

Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.
 

Constraints:

n == rooms.length
2 <= n <= 1000
0 <= rooms[i].length <= 1000
1 <= sum(rooms[i].length) <= 3000
0 <= rooms[i][j] < n
All the values of rooms[i] are unique.
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

// BFS Approach
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    unordered_set<int> visited; // To keep track of visited rooms
    queue<int> qu; // Queue for BFS
    qu.push(0); // Start from room 0
    visited.insert(0); // Mark room 0 as visited

    while(not qu.empty()){
        int curr = qu.front(); // Current room
        qu.pop(); // Remove the room from the queue

        for(auto &neighbor : rooms[curr]){ // Explore all keys in the current room
            if(visited.count(neighbor) == 0){ // If the room is not visited
                qu.push(neighbor); // Add the room to the queue
                visited.insert(neighbor); // Mark the room as visited
            }
        }
    }
    return visited.size() == rooms.size(); // Check if all rooms are visited
}

// DFS Approach
bool dfs(vector<vector<int>> & rooms, unordered_set<int> &visited, int curr){
    visited.insert(curr); // Mark the current room as visited

    for(auto &neighbor : rooms[curr]){ // Explore all keys in the current room
        if(visited.count(neighbor) == 0){ // If the room is not visited
            dfs(rooms, visited, neighbor); // Recur for the room
        }
    }

    return visited.size() == rooms.size(); // Check if all rooms are visited
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    unordered_set<int> visited;
    return dfs(rooms, visited, 0); // Start DFS from room 0
}

int main() {
    vector<vector<int>> rooms = {{1}, {2}, {3}, {}};
    cout << (canVisitAllRooms(rooms) ? "true" : "false") << endl; // Output: true

    rooms = {{1,3}, {3,0,1}, {2}, {0}};
    cout << (canVisitAllRooms(rooms) ? "true" : "false") << endl; // Output: false

    return 0;
}