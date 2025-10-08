/*
Avoid Flood in The City - [Leetcode - 1488(Medium)]
----------------------------------------------------
Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.

Given an integer array rains where:

rains[i] > 0 means there will be rains over the rains[i] lake.
rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
Return an array ans where:

ans.length == rains.length
ans[i] == -1 if rains[i] > 0.
ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.

Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.

Example 1:

Input: rains = [1,2,3,4]
Output: [-1,-1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day full lakes are [1,2,3]
After the fourth day full lakes are [1,2,3,4]
There's no day to dry any lake and there is no flood in any lake.

Example 2:

Input: rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day, we dry lake 2. Full lakes are [1]
After the fourth day, we dry lake 1. There is no full lakes.
After the fifth day, full lakes are [2].
After the sixth day, full lakes are [1,2].
It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.

Example 3:

Input: rains = [1,2,0,1,2]
Output: []
Explanation: After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
After that, it will rain over lakes [1,2]. It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.
 

Constraints:

1 <= rains.length <= 105
0 <= rains[i] <= 109
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

//Approach (Binary search along with map and set and greedy)
//T.C : O(n*logn)
//S.C : O(n)
vector<int> avoidFlood(vector<int>& rains) {
    int n = rains.size();
    
    unordered_map<int, int> mp; // lake -> last rainy day
    set<int> st; // dry days in sorted fashion

    vector<int> result(n, 1);

    for(int i=0; i<n; i++){
        int lake = rains[i];

        if(lake == 0){
            st.insert(i); // Insert dry day into set
        }
        else {
            result[i] = -1;
            // Also check if this lake already contains water, if we will check if we can dry it up
            if(mp.count(lake)){ // Already it has water
                auto itr = st.lower_bound(mp[lake]);

                if(itr == st.end()){ // You won't be able to dry this lake
                    return {};
                }

                // Day on which no rain happened
                int day = *itr;
                result[day] = lake; // Dry this lake on this day
                st.erase(itr); // Remove this day from set
            }
            mp[lake] = i; // Update last rainy day for this lake
        }
    }
    return result;
}

int main() {
    vector<int> rains = {1,2,0,0,2,1};
    vector<int> result = avoidFlood(rains);
    
    if (result.empty()) {
        cout << "[] (Impossible to avoid flood)" << endl;
    } else {
        cout << "[";
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i];
            if (i < result.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    
    return 0;
}