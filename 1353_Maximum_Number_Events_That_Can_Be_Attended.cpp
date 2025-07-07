/*
1353. Maximum Number of Events That Can Be Attended - [Leetcode - 1353(Medium)]
--------------------------------------------------------------------------------
You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.

You can attend an event i at any day d where startTimei <= d <= endTimei. You can only attend one event at any time d.

Return the maximum number of events you can attend.

Example 1:

Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.

Example 2:

Input: events= [[1,2],[2,3],[3,4],[1,2]]
Output: 4


Constraints:

1 <= events.length <= 105
events[i].length == 2
1 <= startDayi <= endDayi <= 105
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int maxEvents(vector<vector<int>> &events) {
    int n = events.size();

    sort(begin(events), end(events)); // sort by starting day

    priority_queue<int, vector<int>, greater<int>> pq; // min-heap to store end days of events
    
    int day = events[0][0]; // current day to attend events
    int i = 0; // index for events
    int count = 0; // result number of events attended

    while (!pq.empty() || i < n) { // while there are events to attend or events in the priority queue

        if (pq.empty()) { // if no events in the queue, move to the next event's start day
            day = events[i][0]; // move to the next event's start day
        }

        while (i < n && events[i][0] == day) { // if the current event starts on this day
            pq.push(events[i][1]); // push its end day into the priority queue
            i++; // move to the next event
        }

        if (!pq.empty()) { // if there are events in the priority queue
            pq.pop(); // 1 event attended on this day
            count++;  // counting the result
        }

        day++; // move to the next day

        // skip those events whose endDay < day
        while (!pq.empty() && pq.top() < day) { // if the earliest ending event ends before the current day
            pq.pop(); // remove it from the queue
        }
    }

    return count;
}

int main(){
    vector<vector<int>> events = {{1, 2}, {2, 3}, {3, 4}};
    cout << "Maximum number of events that can be attended: " << maxEvents(events) << endl;

    events = {{1, 2}, {2, 3}, {3, 4}, {1, 2}};
    cout << "Maximum number of events that can be attended: " << maxEvents(events) << endl;

    return 0;
}