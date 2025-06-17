/*
138. Copy List with Random Pointer - [Leetcode - 138(Medium)]
--------------------------------------------------------------
A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Example 1:

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Constraints:

0 <= n <= 1000
-104 <= Node.val <= 104
Node.random is null or is pointing to some node in the linked list.
*/

#include <iostream>
#include <map>
using namespace std;

class node{
public:
    int value;
    node *next;
    node *random;

    // Constructor
    node(int data){
        value = data;
        next = nullptr;
        random = nullptr;
    }
};

// Approach - 1 => Time = O(n) && Space = O(n)[Using Hashmap];
node *copyRandomList(node *head){
    if (head == nullptr) return nullptr;
    
    map<node *, node *> mp;
    
    node *curr = head;
    node *prev = nullptr;
    node *newHead = nullptr;
    
    while (curr != nullptr){
        node *temp = new node(curr->value);

        mp[curr] = temp; // storing
        
        if (newHead == nullptr){
            newHead = temp;
            prev = newHead;
        }
        else{
            prev->next = temp;
            prev = temp;
        }
        curr = curr->next;
    }
    // Fill Random pointers
    curr = head;
    node *newCurr = newHead;
    
    while (curr != nullptr){
        if (curr->random == nullptr){
            newCurr->random = nullptr;
        }
        else{
            node *deepCopyCorrespondingRandomNode = mp[curr->random];
            newCurr->random = deepCopyCorrespondingRandomNode;
        }
        curr = curr->next;
        newCurr = newCurr->next;
    }
    
    return newHead;
}

// Approach - 2 => Time = O(n) && Space = O(1);
node *copyRandomList(node *head){
    if (head == nullptr) return nullptr;

    // Step 1: Insert the new node between the linked list
    node *curr = head;
    while(curr != nullptr){
        node *currNext = curr->next;
        curr->next = new node(curr->value);
        curr->next->next = currNext;
        curr = currNext;
    }

    // Step 2: Deep copy of random pointer
    curr = head;
    while(curr != nullptr) {
        if(curr->random != nullptr) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // Step 3: Separate the original and copied linked list
    node *newHead = head->next;
    curr = head;
    node *copyCurr = newHead;
    while(curr != nullptr) {
        curr->next = copyCurr->next;
        curr = curr->next;
        if(curr != nullptr) {
            copyCurr->next = curr->next;
            copyCurr = copyCurr->next;
        }
    }

    return newHead;
}

int main () {
    node *head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);

    // Setting up random pointers
    head->random = head->next;           // 1's random -> 2
    head->next->random = head->next;     // 2's random -> 2
    head->next->next->random = nullptr;  // 3's random -> nullptr

    // Copy the list
    node *copiedHead = copyRandomList(head);

    // Print copied list to verify (optional)
    node *curr = copiedHead;
    while (curr) {
        cout << "Value: " << curr->value << ", Random: ";
        if (curr->random) cout << curr->random->value;
        else cout << "null";
        
        cout << endl;
        curr = curr->next;
    }
    return 0;
}