/*
INTERSECTION OF TWO LINKED LIST - (LEETCODE - 160) - EASY

Example 1:

Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
- Note that the intersected node's value is not 1 because the nodes with value 1 in A and B (2nd node in A and 3rd node in B) are different node references. In other words, they point to two different locations in memory, while the nodes with value 8 in A and B (3rd node in A and 4th node in B) point to the same location in memory.

Example 2:

Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.

Example 3:

Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.

*/

#include <iostream>
using namespace std;

// Define the node structure
class node {
public:
    int data;
    node* next;
    node(int val) : data(val), next(nullptr) {}
};

// Function to find the intersection of two linked list
node *getIntersectionNode(node *headA, node *headB){
    if (!headA || !headB) return nullptr;

    node* a = headA;
    node* b = headB;

    // Traverse both lists. When one pointer reaches the end, redirect it to the head of the other list.
    // If the lists intersect, the pointers will meet at the intersection node after at most 2 passes.
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a; // Can be nullptr (no intersection) or the intersection node
}

int main(){

    // Example usage:
    // Creating two intersecting linked lists for demonstration:
    // List A: 1 -> 2 \
    //                  3 -> 4 -> 5
    // List B:    6  /

    node* common = new node(3);
    common->next = new node(4);
    common->next->next = new node(5);

    node* headA = new node(1);
    headA->next = new node(2);
    headA->next->next = common;

    node* headB = new node(6);
    headB->next = common;

    node* intersection = getIntersectionNode(headA, headB);
    if (intersection) {
        cout << "Intersected at '" << intersection->data << "'" << endl;
    }
    else {
        cout << "No intersection" << endl;
    }

    return 0;
}