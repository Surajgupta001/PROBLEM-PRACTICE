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

class node{
    public:
    int value;
    node* next;

    //constructor
    node(int data){

        value = data;
        next = nullptr;
    }
};

class LinkedList{
    public:
    node *head;

    // constructor
    LinkedList(){
        head = nullptr;
    }

    // insertion
    void insertAtTail(int data){
        node *newNode = new node(data);
        if(head == nullptr){
            head = newNode;
            return;
        }
        node *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void display(){
        node *temp = head;
        while(temp != nullptr){
            cout<<temp->value<<"->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

// Function to find the intersection of two linked list
node *getIntersectionNode(node *headA, node *headB){
    /*
    * Time: O(n+m) - Length of two linked list
    * Space: O(1) - No extra space is used
    */ 
    if(!headA || !headB) return nullptr;
    node *ptr_1 = headA;
    node *ptr_2 = headB;
    // Move to the next node or to the head of the other list
    while(ptr_1 != ptr_2){
        /*
        * condition ? expression1 : expression2;

        => if condition is true, expression1 is executed.
        => if condition is false, expression2 is executed.
        */ 
        ptr_1 = ptr_1 ? ptr_1->next : headB;
        ptr_2 = ptr_2 ? ptr_2->next : headA;
    }
    // will be null if there's no intersection
    return ptr_1; 
}

/*
same but Different way of writing

node *getIntersectionNode(node *headA, node *headB) {
    node *ptrA = headA;
    node *ptrB = headB;

    while (ptrA != ptrB) {
        if (ptrA != nullptr) {
            ptrA = ptrA->next;
        } else {
            ptrA = headB;
        }

        if (ptrB != nullptr) {
            ptrB = ptrB->next;
        } else {
            ptrB = headA;
        }
    }

    return ptrA;
}
*/ 

int main(){

    LinkedList listA; 
    listA.insertAtTail(1);
    listA.insertAtTail(9);
    listA.insertAtTail(1);
    listA.insertAtTail(2);
    listA.insertAtTail(4);

    LinkedList listB;
    listB.insertAtTail(3);
    listB.insertAtTail(2);
    listB.insertAtTail(4);

    node *temp = listB.head;
    // Move to the intersection node
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = listA.head->next->next->next; // make the list intersect

    cout<<"List A: ";
    listA.display();

    cout<<"List B: ";
    listB.display();

    node *intersection = getIntersectionNode(listA.head, listB.head);
    if(intersection){
        cout<<"Intersection node is: "<<intersection->value<<endl;
    }
    else{
        cout<<"No intersection"<<endl;
    }
    
    return 0;
}