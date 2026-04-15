/*
Robot Collisions - [Leetcode - 2751(Hard)]
----------------------------------------------
There are n 1-indexed robots, each having a position on a line, health, and movement direction.

You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.

All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.

If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.

Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final health of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.

Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.

Note: The positions may be unsorted.

Example 1:

Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
Output: [2,17,9,15,10]
Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].

Example 2:

Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
Output: [14]
Explanation: There are 2 collisions in this example. Firstly, robot 1 and robot 2 will collide, and since both have the same health, they will be removed from the line. Next, robot 3 and robot 4 will collide and since robot 4's health is smaller, it gets removed, and robot 3's health becomes 15 - 1 = 14. Only robot 3 remains, so we return [14].

Example 3:

Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
Output: []
Explanation: Robot 1 and robot 2 will collide and since both have the same health, they are both removed. Robot 3 and 4 will collide and since both have the same health, they are both removed. So, we return an empty array, [].

Constraints:

1 <= positions.length == healths.length == directions.length == n <= 10^5
1 <= positions[i], healths[i] <= 10^9
directions[i] == 'L' or directions[i] == 'R'
All values in positions are distinct
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
    int n = positions.size();
    
    vector<int> actual_index(n); // 0, 1, 2, .....n-1
    for(int i = 0; i < n; i++) {
        actual_index[i] = i;
    }

    // Another way to fill the actual_index vector is to use iota function from numeric header
    // #include <numeric>
    // iota(actual_index.begin(), actual_index.end(), 0); // Fills the vector with 0, 1, 2, ..., n-1

    auto lambda = [&](int a, int b) {
        return positions[a] < positions[b];
    };

    // Sort the robots based on their positions
    sort(actual_index.begin(), actual_index.end(), lambda);

    vector<int> result;
    stack<int> st; // Stack to keep track of robots moving to the right

    for(auto &currIdx : actual_index){
        if(directions[currIdx] == 'R'){
            st.push(currIdx);
        } else { // Towards Left
            while(!st.empty() && healths[currIdx] > 0){
                int topIdx = st.top();
                st.pop();

                if(healths[topIdx] > healths[currIdx]){
                    healths[topIdx] -= 1;
                    healths[currIdx] = 0;
                    st.push(topIdx);                
                } else if(healths[topIdx] < healths[currIdx]){
                    healths[currIdx] -= 1;
                    healths[topIdx] = 0;
                } else { // Both have same health
                    healths[topIdx] = 0;
                    healths[currIdx] = 0;
                }
            }
        }
    }
    // Collect the surviving robots
    for(int i = 0; i < n; i++) {
        if(healths[i] > 0) {
            result.push_back(healths[i]);
        }
    }
    return result;
}

int main() {
    vector<int> positions = {3,5,2,6};
    vector<int> healths = {10,10,15,12};
    string directions = "RLRL";

    vector<int> result = survivedRobotsHealths(positions, healths, directions);
    for(int health : result) {
        cout << health << " ";
    }
    cout << endl;

    return 0;
}