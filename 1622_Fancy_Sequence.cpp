/*
Fancy Sequence - [Leetcode - 1622(Hard)]
-------------------------------------------
Write an API that generates fancy sequences using the append, addAll, and multAll operations.

Implement the Fancy class:

Fancy() Initializes the object with an empty sequence.
void append(val) Appends an integer val to the end of the sequence.
void addAll(inc) Increments all existing values in the sequence by an integer inc.
void multAll(m) Multiplies all existing values in the sequence by an integer m.
int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7. If the index is greater or equal than the length of the sequence, return -1.
 

Example 1:

Input
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
Output
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

Explanation
Fancy fancy = new Fancy();
fancy.append(2);   // fancy sequence: [2]
fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
fancy.append(7);   // fancy sequence: [5, 7]
fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // return 10
fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
fancy.append(10);  // fancy sequence: [13, 17, 10]
fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // return 26
fancy.getIndex(1); // return 34
fancy.getIndex(2); // return 20
 

Constraints:

1 <= val, inc, m <= 100
0 <= idx <= 10^5
At most 105 calls total will be made to append, addAll, multAll, and getIndex.
*/ 

#include <iostream>
#include <vector>
using namespace std;

//Approach - Simple maths + Binary Exponentiation and Fermat's Little Theorem
//T.C : O(log(M)) for Binary Exponentiation power(mult, M-2)
//S.C : O(1)
long long mod = 1e9 + 7;
#define ll long long

vector<ll> seq;
ll add = 0;
ll mult = 1;

// Binary Exponentiation function to calculate (base^exp) % mod -> using Fermat's Little Theorem
ll power(ll a, ll b) {
    if(b == 0) return 1;

    ll half = power(a, b / 2);
    ll result = (half * half) % mod;

    if(b % 2 == 1){
        result = (result * a) % mod;
    }

    return result;
}
class Fancy {
public:
    Fancy() {
        seq.clear();
    }
    
    void append(int val) {
        ll x = ((val - add + mod) % mod * power(mult, mod - 2)) % mod;
        seq.push_back(x);
    }
    
    void addAll(int inc) {
        add = (add + inc) % mod;
    }
    
    void multAll(int m) {
        mult = (mult * m) % mod;
        add = (add * m) % mod;
    }
    
    int getIndex(int idx) {
        if(idx >= seq.size()) return -1;
        ll x = (seq[idx] * mult + add) % mod;
        return (int)x;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */

int main() {
    Fancy fancy;
    fancy.append(2);   // fancy sequence: [2]
    fancy.addAll(3);   // fancy sequence: [5]
    fancy.append(7);   // fancy sequence: [5, 7]
    fancy.multAll(2);  // fancy sequence: [10, 14]
    cout << fancy.getIndex(0) << endl; // return 10
    fancy.addAll(3);   // fancy sequence: [13, 17]
    fancy.append(10);  // fancy sequence: [13, 17, 10]
    fancy.multAll(2);  // fancy sequence: [26, 34, 20]
    cout << fancy.getIndex(0) << endl; // return 26
    cout << fancy.getIndex(1) << endl; // return 34
    cout << fancy.getIndex(2) << endl; // return 20

    return 0;
}