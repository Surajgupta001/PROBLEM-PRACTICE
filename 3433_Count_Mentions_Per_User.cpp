/*
Count Mentions Per User - [Leetcode - 3433(Medium)]
-----------------------------------------------------
You are given an integer numberOfUsers representing the total number of users and an array events of size n x 3.

Each events[i] can be either of the following two types:

1. Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
   • This event indicates that a set of users was mentioned in a message at timestampi.
   • The mentions_stringi string can contain one of the following tokens:
     • id<number>: where <number> is an integer in range [0,numberOfUsers - 1]. There can be multiple ids separated by a single whitespace and may contain duplicates. This can mention even the offline users.
     • ALL: mentions all users.
     • HERE: mentions all online users.

2. Offline Event: ["OFFLINE", "timestampi", "idi"]
   • This event indicates that the user idi had become offline at timestampi for 60 time units. The user will automatically be online again at time timestampi + 60.

Return an array mentions where mentions[i] represents the number of mentions the user with id i has across all MESSAGE events.

All users are initially online, and if a user goes offline or comes back online, their status change is processed before handling any message event that occurs at the same timestamp.

Note that a user can be mentioned multiple times in a single message event, and each mention should be counted separately.

 

Example 1:

Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]

Output: [2,2]

Explanation:

Initially, all users are online.

At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]

At timestamp 11, id0 goes offline.

At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]

Example 2:

Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]

Output: [2,2]

Explanation:

Initially, all users are online.

At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]

At timestamp 11, id0 goes offline.

At timestamp 12, "ALL" is mentioned. This includes offline users, so both id0 and id1 are mentioned. mentions = [2,2]

Example 3:

Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]

Output: [0,1]

Explanation:

Initially, all users are online.

At timestamp 10, id0 goes offline.

At timestamp 12, "HERE" is mentioned. Because id0 is still offline, they will not be mentioned. mentions = [0,1]

Constraints:

1 <= numberOfUsers <= 100
1 <= events.length <= 100
events[i].length == 3
events[i][0] will be one of MESSAGE or OFFLINE.
1 <= int(events[i][1]) <= 105
The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
0 <= <number> <= numberOfUsers - 1
It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

//Approach - Simply sort and simulate
//T.C : O(E log E + E * N), N = number of users , E = number of events
//S.C : O(N + E)
void applyMessageEvent(vector<string>event, vector<int>&mentionCount, vector<int>&offlineTime){
    int timestamp = stoi(event[1]);
    
    vector<string> ids;
    
    stringstream ss(event[2]);
    
    string token;
    while(ss >> token){
        ids.push_back(token);
    }
    
    //Process all IDs
    for(string id : ids) {
        if(id == "ALL") {
            for(int i = 0; i<mentionCount.size(); i++) {
                mentionCount[i]++;
            }
        } else if(id == "HERE") {
            for(int i = 0; i < mentionCount.size(); i++){
                if(offlineTime[i] == 0 || offlineTime[i] + 60 <= timestamp){
                    mentionCount[i]++;
                }
            }
        } else {
            mentionCount[stoi(id.substr(2))]++; //fetch id value i.e. x from idx (id0, id1 etc)
        }
    }
}

vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
    vector<int>mentionCount(numberOfUsers);
    vector<int>offlineTime(numberOfUsers);
    
    // You can use a custom comparator function instead of lambda if needed, here we use lambda for simplicity
    auto lambda=[](vector<string>& vec1, vector<string>& vec2) {
        int t1 = stoi(vec1[1]);
        int t2 = stoi(vec2[1]);
        
        if(t1 == t2) {
            return vec1[0][1] > vec2[0][1]; //comparing 'O' of "OFFLINE" with 'M' of "MESSAGE"
            //OFFLINE should come first
        }
        
        return t1 < t2;
    };
    
    sort(events.begin(), events.end(), lambda);
    
    for(vector<string>event: events){
        if(event[0] == "MESSAGE") {
            applyMessageEvent(event, mentionCount, offlineTime);
        }
        else if(event[0] == "OFFLINE") {
            int timestamp = stoi(event[1]);
            int id = stoi(event[2]);
            offlineTime[id] = timestamp;
        }
    }

    return mentionCount;
}

int main() {
    int numberOfUsers = 2;
    vector<vector<string>> events = {{"MESSAGE","10","id1 id0"}, {"OFFLINE","11","0"}, {"MESSAGE","71","HERE"}};
    
    vector<int> result = countMentions(numberOfUsers, events);
    
    for(int count : result) {
        cout << count << " ";
    }
    
    return 0;
}