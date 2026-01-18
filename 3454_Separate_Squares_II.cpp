/*
Separate Squares II - [Leetcode - 3454(Hard)]
------------------------------------------------
You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted only once in this version.

Example 1:

Input: squares = [[0,0,1],[2,2,1]]

Output: 1.00000

Explanation:

Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.

Example 2:

Input: squares = [[0,0,2],[1,1,1]]

Output: 1.00000

Explanation:

Since the blue square overlaps with the red square, it will not be counted again. Thus, the line y = 1 splits the squares into two equal parts.

Constraints:

1 <= squares.length <= 5 * 10^4
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 10^9
1 <= li <= 10^9
The total area of all the squares will not exceed 10^15.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct SegTree {
    vector<int> cnt;
    vector<long double> len;
    vector<long long> xs;
    int n;
    SegTree() : n(0) {}
    SegTree(const vector<long long> &xs_) { init(xs_); }
    void init(const vector<long long> &xs_) {
        xs = xs_;
        n = (int)xs.size() - 1;
        cnt.assign(4 * n, 0);
        len.assign(4 * n, 0);
    }
    void pull(int idx, int l, int r) {
        if (cnt[idx] > 0) {
            len[idx] = (long double)(xs[r] - xs[l]);
        }
        else if (l + 1 == r) {
            len[idx] = 0;
        }
        else {
            len[idx] = len[idx << 1] + len[idx << 1 | 1];
        }
    }
    void update(int idx, int l, int r, int ql, int qr, int delta) {
        if (ql >= r || qr <= l)
            return;
        if (ql <= l && r <= qr) {
            cnt[idx] += delta;
            pull(idx, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        update(idx << 1, l, mid, ql, qr, delta);
        update(idx << 1 | 1, mid, r, ql, qr, delta);
        pull(idx, l, r);
    }
    long double covered() const { return len[1]; }
};

struct Event {
    long long y;
    int l, r;
    int delta; // +1 add, -1 remove
    bool operator<(const Event &other) const {
        if (y != other.y)
            return y < other.y;
        return delta > other.delta; // add before remove if tied
    }
};

double separateSquares(vector<vector<int>> &squares) {
    int n = (int)squares.size();
    vector<long long> xs;
    xs.reserve(2 * n);
    vector<Event> events;
    events.reserve(2 * n);

    for (auto &s : squares) {
        long long x = s[0], y = s[1], l = s[2];
        xs.push_back(x);
        xs.push_back(x + l);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    auto idx = [&](long long x) {
        return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
    };

    for (auto &s : squares) {
        long long x = s[0], y = s[1], l = s[2];
        int L = idx(x);
        int R = idx(x + l);
        events.push_back({y, L, R, +1});
        events.push_back({y + l, L, R, -1});
    }
    sort(events.begin(), events.end());
    if (events.empty())
        return 0.0;

    auto total_area = [&]() -> long double {
        SegTree st(xs);
        long long prevY = events[0].y;
        long double Lcov = 0, area = 0;
        size_t i = 0;
        while (i < events.size()) {
            long long y = events[i].y;
            area += Lcov * (long double)(y - prevY);
            while (i < events.size() && events[i].y == y) {
                st.update(1, 0, st.n, events[i].l, events[i].r, events[i].delta);
                i++;
            }
            Lcov = st.covered();
            prevY = y;
        }
        return area;
    };

    long double total = total_area();
    long double half = total / 2.0L;

    // Second pass: find minimal y where cumulative area >= half
    SegTree st(xs);
    long long prevY = events[0].y;
    long double Lcov = 0, acc = 0;
    size_t i = 0;
    while (i < events.size()) {
        long long y = events[i].y;
        long double segmentH = (long double)(y - prevY);
        long double adds = Lcov * segmentH;
        if (acc + adds >= half - 1e-18L) {
            if (Lcov == 0)
                return (double)prevY;
            long double t = (half - acc) / Lcov;
            long double ans = (long double)prevY + t;
            return (double)ans;
        }
        acc += adds;
        while (i < events.size() && events[i].y == y) {
            st.update(1, 0, st.n, events[i].l, events[i].r, events[i].delta);
            i++;
        }
        Lcov = st.covered();
        prevY = y;
    }
    return (double)prevY; // half == total ⇒ last y boundary
}

int main() {
    vector<vector<int>> squares1 = {{0, 0, 1}, {2, 2, 1}};
    vector<vector<int>> squares2 = {{0, 0, 2}, {1, 1, 1}};
    cout.setf(std::ios::fixed);
    cout << setprecision(5);
    cout << separateSquares(squares1) << "\n"; // 1.00000
    cout << separateSquares(squares2) << "\n"; // 1.00000
    return 0;
}