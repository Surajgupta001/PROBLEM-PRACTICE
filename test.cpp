#include <iosstream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

class Solution {
public:

    void updateTree(vector<int>& segmentTree, int i, int low, int high, int idx, int value){

        if (low == high) {
            segmentTree[i] = value;
            return;
        }

        int mid = low + (high - low) / 2;

        if (idx <= mid)
            updateTree(segmentTree, 2 * i + 1, low, mid, idx, value);
        else
            updateTree(segmentTree, 2 * i + 2, mid + 1, high, idx, value);

        segmentTree[i] = max(segmentTree[2 * i + 1], segmentTree[2 * i + 2]);
    }

    int getMax(vector<int>& segmentTree,
               int i,
               int low,
               int high,
               int left,
               int right) {

        if (low > right || high < left)
            return INT_MIN;

        if (low >= left && high <= right)
            return segmentTree[i];

        int mid = low + (high - low) / 2;

        int leftMax =
            getMax(segmentTree, 2 * i + 1, low, mid, left, right);

        int rightMax =
            getMax(segmentTree, 2 * i + 2, mid + 1, high, left, right);

        return max(leftMax, rightMax);
    }

    vector<bool> getResults(vector<vector<int>>& queries) {

        int n = 50000;

        vector<int> segmentTree(4 * n + 1, 0);

        set<int> obstacles;
        obstacles.insert(0);

        vector<bool> result;

        for (auto& query : queries) {

            // Type 1 Query
            if (query[0] == 1) {

                int x = query[1];

                auto itr = obstacles.upper_bound(x);

                int nextObstacle =
                    (itr != obstacles.end()) ? *itr : n;

                int prevObstacle = *prev(itr);

                updateTree(segmentTree,
                           0,
                           0,
                           n - 1,
                           x,
                           x - prevObstacle);

                if (nextObstacle != n) {
                    updateTree(segmentTree,
                               0,
                               0,
                               n - 1,
                               nextObstacle,
                               nextObstacle - x);
                }

                obstacles.insert(x);
            }

            // Type 2 Query
            else {

                int x = query[1];
                int size = query[2];

                auto itr = obstacles.upper_bound(x);

                int prevObstacle = *prev(itr);

                int maxGap =
                    getMax(segmentTree,
                           0,
                           0,
                           n - 1,
                           0,
                           prevObstacle);

                int bestGap =
                    max(maxGap, x - prevObstacle);

                result.push_back(bestGap >= size);
            }
        }

        return result;
    }
};