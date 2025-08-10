/*
Remove Nodes From Linked List - [Leetcode - 2487(Medium)]
----------------------------------------------------------
You are given the head of a linked list.

Remove every node which has a node with a greater value anywhere to the right side of it.

Return the head of the modified linked list.

Example 1:

Input: head = [5,2,13,3,8]
Output: [13,8]
Explanation: The nodes that should be removed are 5, 2 and 3.
- Node 13 is to the right of node 5.
- Node 13 is to the right of node 2.
- Node 8 is to the right of node 3.

Example 2:

Input: head = [1,1,1,1]
Output: [1,1,1,1]
Explanation: Every node has value 1, so no nodes are removed.

Constraints:

The number of the nodes in the given list is in the range [1, 105].
1 <= Node.val <= 105
*/

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

class node {
public:
    int value;
    node *next;

    // Constructor
    node(int data){
        value = data;
        next = nullptr;
    }
};

/* Approach - 1: Reverse-and-filter (O(1) extra space):
                  => Reverse list.
                  => Traverse left-to-right keeping nodes that are >= max_so_far; update max_so_far.
                  => Reverse again to restore order.
*/

node *reverseList(node *curr) {
    node *prev = nullptr;
    while (curr) {
        node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

node* removeNodes(node* head) {
    if (!head) return nullptr;

    node* revHead = reverseList(head);
    int max_so_far = INT_MIN;

    node* prev = nullptr;
    node* curr = revHead;

    while (curr) {
        if (curr->value >= max_so_far) {
            max_so_far = curr->value;
            prev = curr;
            curr = curr->next;
        } else {
            // remove curr from the reversed list
            node* toDelete = curr;
            curr = curr->next;
            if (prev) {
                prev->next = curr;
            } else {
                // deleting the head of the reversed list
                revHead = curr;
            }
            delete toDelete;
        }
    }

    return reverseList(revHead);
}

/* Approach - 2 : Recursive (O(n) stack space):
                 => Process to the tail; on unwinding, drop current node if its value < next kept node’s value.
*/
node* removeNodes(node* head) {
    if (!head || !head->next) return head;

    head->next = removeNodes(head->next);

    if (head->next && head->value < head->next->value) {
        node* keep = head->next; // save next before deleting
        delete head;
        return keep;
    }
    return head;
}

/* Approach - 3 : Monotonic stack/list (O(n) extra space)
                  => Traverse from head; maintain decreasing stack of values/nodes; pop while top < current value; link remaining.
*/
node* removeNodes(node* head) {
    if (!head) return nullptr;

    vector<node*> st;  // monotonic decreasing stack by value

    node* curr = head;
    while (curr) {
        while (!st.empty() && st.back()->value < curr->value) {
            node* dropped = st.back();
            st.pop_back();
            delete dropped; // prevent memory leak
        }
        st.push_back(curr);
        curr = curr->next;
    }

    // Rebuild the list from kept nodes
    node* newHead = nullptr;
    node* tail = nullptr;
    for (node* p : st) {
        if (!newHead) {
            newHead = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
    if (tail) tail->next = nullptr;

    return newHead;
}

int main() {
    // Create a linked list: 5 -> 2 -> 13 -> 3 -> 8
    node *head = new node(5);
    head->next = new node(2);
    head->next->next = new node(13);
    head->next->next->next = new node(3);
    head->next->next->next->next = new node(8);

    // Remove nodes
    head = removeNodes(head);

    // Print the modified linked list
    node *curr = head;
    while (curr) {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;

    // Free memory
    while (head) {
        node *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}