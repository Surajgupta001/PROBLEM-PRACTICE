/*
Maximum Twin Sum of a Linked List - [Leetcode - 2130(Medium)]
-------------------------------------------------------------------

In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.

Example 1:

Input: head = [5,4,2,1]
Output: 6
Explanation:
Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
There are no other nodes with twins in the linked list.
Thus, the maximum twin sum of the linked list is 6. 

Example 2:

Input: head = [4,2,2,3]
Output: 7
Explanation:
The nodes with twins present in this linked list are:
- Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
- Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
Thus, the maximum twin sum of the linked list is max(7, 4) = 7. 

Example 3:

Input: head = [1,100000]
Output: 100001
Explanation:
There is only one node with a twin in the linked list having twin sum of 1 + 100000 = 100001.
 

Constraints:

The number of nodes in the list is an even integer in the range [2, 10^5].
1 <= Node.val <= 10^5
*/

class ListNode {
public:
    int value;
    ListNode* next;

    // Constructor to initialize the node with a value and an optional next pointer
    ListNode(int val) {
        value = val;
        next = nullptr;
    }
};

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Approach - 1 : Using Vector
int pairSum(ListNode* head) {
    vector<int> vec;

    while(head != nullptr){
        vec.push_back(head->value);
        head = head->next;
    }

    int result = 0;


    int i = 0, j = vec.size() - 1;
    while(i < j){
        result = max(result, vec[i] + vec[j]);
        i++;
        j--;
    }
    return result;
}

// Approch - 2 : Using Stack
int pairSum(ListNode* head) {
    stack<int> st;
    ListNode* curr = head;

    while(curr != nullptr){
        st.push(curr->value);
        curr = curr->next;
    }

    int N = st.size();
    curr = head;

    int count = 1;
    int result = 0;

    while(count <= N/2){
        result = max(result, curr->value + st.top());
        curr = curr->next;
        st.pop();
        count++;
    }
    return result;
}

// Approach - 3 : Reverse the second half of the linked list and calculate the twin sum
int pairSum(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Find the middle of the linked list
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list
    ListNode* prev = nullptr;
    ListNode* curr = slow;
    while(curr != nullptr){
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    // Calculate the twin sum
    int result = 0;
    ListNode* firstHalf = head;
    ListNode* secondHalf = prev; // 'prev' is now the head of the reversed second half

    while(secondHalf != nullptr){
        result = max(result, firstHalf->value + secondHalf->value);
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return result;
}

int main() {
    // Example usage:
    ListNode* head = new ListNode(5);
    head->next = new ListNode(4);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);

    cout << pairSum(head) << endl; // Output: 6

    return 0;
}