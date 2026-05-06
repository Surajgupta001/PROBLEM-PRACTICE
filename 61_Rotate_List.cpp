/*
Rotate List - [Leetcode - 61(Medium)]
--------------------------------------------
Given the head of a linked list, rotate the list to the right by k places.

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:

Input: head = [0,1,2], k = 4
Output: [2,0,1]

Constraints:

The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 10^9
*/

#include <iostream>
#include <vector>
using namespace std;
class ListNode {
    public:
    int value;
    ListNode* next;

    // Constructor
    ListNode(int data){
        this->value = data;
        this->next = nullptr;
    }
};

ListNode* rotateRight(ListNode* head, int k) {
    if(!head || !head->next || k == 0) return head;

    int length = 1; // Calculate the length of the linked list

    ListNode* tail = head;

    while(tail-> next != nullptr){
        tail = tail->next;
        length++;
    }

    k = k % length; // Handle cases where k is greater than the length of the list

    if(k == 0) return head; // If k is 0 after modulus, return the original list

    // Circular Connect
    tail->next = head; // Connect the tail to the head to make it circular

    // Find the new tail (node at position length - k)
    int remain = length - k; // number of nodes before the new head
    ListNode* newTail = head;

    // Move (remain - 1) steps to reach the new tail (since head is at position 1)
    for (int i = 1; i < remain; ++i) {
        newTail = newTail->next;
    }

    ListNode* newHead = newTail->next; // The new head is the node after the new tail
    newTail->next = nullptr; // Break the circular connection to finalize the rotated list

    return newHead;
}

int main() {
    // Example usage:
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;
    ListNode* rotatedHead = rotateRight(head, k);

    // Print the rotated list
    ListNode* current = rotatedHead;
    while (current) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

    return 0;
}