/*
Implement Router - [Leetcode - 3508(Medium)]
---------------------------------------------
Design a data structure that can efficiently manage data packets in a network router. Each data packet consists of the following attributes:

source: A unique identifier for the machine that generated the packet.
destination: A unique identifier for the target machine.
timestamp: The time at which the packet arrived at the router.
Implement the Router class:

Router(int memoryLimit): Initializes the Router object with a fixed memory limit.

memoryLimit is the maximum number of packets the router can store at any given time.
If adding a new packet would exceed this limit, the oldest packet must be removed to free up space.
bool addPacket(int source, int destination, int timestamp): Adds a packet with the given attributes to the router.

A packet is considered a duplicate if another packet with the same source, destination, and timestamp already exists in the router.
Return true if the packet is successfully added (i.e., it is not a duplicate); otherwise return false.
int[] forwardPacket(): Forwards the next packet in FIFO (First In First Out) order.

Remove the packet from storage.
Return the packet as an array [source, destination, timestamp].
If there are no packets to forward, return an empty array.
int getCount(int destination, int startTime, int endTime):

Returns the number of packets currently stored in the router (i.e., not yet forwarded) that have the specified destination and have timestamps in the inclusive range [startTime, endTime].
Note that queries for addPacket will be made in increasing order of timestamp.

 

Example 1:

Input:
["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
[[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]]

Output:
[null, true, true, false, true, true, [2, 5, 90], true, 1]

Explanation

Router router = new Router(3); // Initialize Router with memoryLimit of 3.
router.addPacket(1, 4, 90); // Packet is added. Return True.
router.addPacket(2, 5, 90); // Packet is added. Return True.
router.addPacket(1, 4, 90); // This is a duplicate packet. Return False.
router.addPacket(3, 5, 95); // Packet is added. Return True
router.addPacket(4, 5, 105); // Packet is added, [1, 4, 90] is removed as number of packets exceeds memoryLimit. Return True.
router.forwardPacket(); // Return [2, 5, 90] and remove it from router.
router.addPacket(5, 2, 110); // Packet is added. Return True.
router.getCount(5, 100, 110); // The only packet with destination 5 and timestamp in the inclusive range [100, 110] is [4, 5, 105]. Return 1.

Example 2:

Input:
["Router", "addPacket", "forwardPacket", "forwardPacket"]
[[2], [7, 4, 90], [], []]

Output:
[null, true, [7, 4, 90], []]

Explanation

Router router = new Router(2); // Initialize Router with memoryLimit of 2.
router.addPacket(7, 4, 90); // Return True.
router.forwardPacket(); // Return [7, 4, 90].
router.forwardPacket(); // There are no packets left, return [].
 

Constraints:

2 <= memoryLimit <= 105
1 <= source, destination <= 2 * 105
1 <= timestamp <= 109
1 <= startTime <= endTime <= 109
At most 105 calls will be made to addPacket, forwardPacket, and getCount methods altogether.
queries for addPacket will be made in increasing order of timestamp.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Router {
public:
    int max_size; // Maximum memory limit
    unordered_map<string, vector<int>> packetStore; // To store packets with key as "source-destination-timestamp"
    unordered_map<int, vector<int>> destTimeMap; // destination -> list of timestamps
    queue<string> qu; // To maintain FIFO order
    Router(int memoryLimit) {
        max_size = memoryLimit;
    }

    string makeKey(int source, int destination, int timestamp) {
        return to_string(source) + "-" + to_string(destination) + "-" + to_string(timestamp);
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        string key = makeKey(source, destination, timestamp);
        if (packetStore.find(key) != packetStore.end()) {
            return false; // Duplicate packet
        }
        
        // If memory limit exceeded, forward the oldest packet
        if(qu.size() >= max_size) {
            forwardPacket();
        }

        // Add new packet
        packetStore[key] = {source, destination, timestamp};
        qu.push(key); // Maintaining FIFO order
        destTimeMap[destination].push_back(timestamp); // Storing timestamp for destination
        return true; // Packet added successfully
    }
    
    vector<int> forwardPacket() {
        if (qu.empty()) {
            return {};
        }

        string key = qu.front();
        qu.pop();

        // Remove packet from store and return it
        vector<int> packet = packetStore[key];
        packetStore.erase(key); // Remove from packet store

        int destination = packet[1];
        destTimeMap[destination].erase(destTimeMap[destination].begin()); // Remove timestamp from destination map

        return packet; // Return the forwarded packet
    }
    
    int getCount(int destination, int startTime, int endTime) {
        auto itr = destTimeMap.find(destination);
        if (itr == destTimeMap.end() || itr->second.empty()) {
            return 0; // No packets for this destination
        }

        vector<int>& timestamps = itr->second;

        int lowerBound = lower_bound(timestamps.begin(), timestamps.end(), startTime) - timestamps.begin();
        int upperBound = upper_bound(timestamps.begin(), timestamps.end(), endTime) - timestamps.begin();

        return upperBound - lowerBound;
    }
};

/*
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
*/

int main() {
    Router router(3); // Initialize Router with memoryLimit of 3.
    cout << boolalpha << router.addPacket(1, 4, 90) << endl; // Packet is added. Return True.
    cout << boolalpha << router.addPacket(2, 5, 90) << endl; // Packet is added. Return True.
    cout << boolalpha << router.addPacket(1, 4, 90) << endl; // This is a duplicate packet. Return False.
    cout << boolalpha << router.addPacket(3, 5, 95) << endl; // Packet is added. Return True
    cout << boolalpha << router.addPacket(4, 5, 105) << endl; // Packet is added, [1, 4, 90] is removed as number of packets exceeds memoryLimit. Return True.
    
    vector<int> forwardedPacket = router.forwardPacket(); // Return [2, 5, 90] and remove it from router.
    if (!forwardedPacket.empty()) {
        cout << "[" << forwardedPacket[0] << ", " << forwardedPacket[1] << ", " << forwardedPacket[2] << "]" << endl;
    } else {
        cout << "[]" << endl;
    }

    cout << boolalpha << router.addPacket(5, 2, 110) << endl; // Packet is added. Return True.
    cout << router.getCount(5, 100, 110) << endl; // The only packet with destination 5 and timestamp in the inclusive range [100, 110] is [4, 5, 105]. Return 1.

    return 0;
}