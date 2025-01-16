/*
Pattern : Slow & Fast Pointer

LINKED LIST CYCLE - (LEETCODE -141)
=============================================
Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

Example 2:


Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
*/ 
#include <iostream>
using namespace std;

class node{
    public:
    int value;
    node *next;

    // constructor
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

    void insertAtTail(int value){
        node *newNode = new node(value);
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
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

// Checking circle in linked list
bool isCirclePresent(node *head){

    if(!head){
        return false;
    }

    node *slow = head;
    node *fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast){
            cout<<slow->value<<endl;
            return true; // i.e. cycle is present.
        }
    }
    return false; // i.e. cycle is not present.
}

int main(){

    LinkedList ll;

    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(0);
    ll.insertAtTail(-4);
    ll.display();

    cout<<"The value is: ";
    // Create a cycle in the Linked List
    node *temp = ll.head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = ll.head->next; // Connect the last node to the second node.
    
    cout<<"Circle Present: "<<isCirclePresent(ll.head)<<endl;

    return 0;
}