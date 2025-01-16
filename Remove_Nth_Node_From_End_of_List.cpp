/*
Remove Nth Node From End of List - [Leetcode - 19(Medium)]
=============================================================
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:

Input: head = [1], n = 1
Output: []

Example 3:

Input: head = [1,2], n = 1
Output: [1]
*/ 

#include <iostream>
using namespace std;

class node {
    public:
    int value;
    node* next;

    // Constructor
    node(int data){
        value = data;
        next = nullptr;
    }
};

class linkedList{
    public:
    node* head;

    // Constructor
    linkedList(){
        head = nullptr;
    }

    void insertAtTail(int value){
        node* newNode = new node(value);
        if (head == nullptr){ // linked list is empty
            head = newNode;
            return;
        }
        else{
            node* temp = head;
            while(temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
    }
    void display(){
        node* temp = head;
        while(temp != nullptr){
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

// Function to remove the Nth node from the end of the linked list
node *removeNthFromEnd(node *head, int n) {
    node *fast = head;
    node *slow = head;

    // Move fast pointer n steps ahead
    for(int i=0;i<n;i++) fast = fast->next;

    // If fast is null, we need to remove the head node
    if(fast == nullptr) return head->next; // Return the new head

    // Move both pointers until fast reaches the end
    while(fast->next != nullptr){
        fast = fast->next;
        slow = slow->next;
    }

    // Remove the Nth node from the end
    slow->next = slow->next->next;

    return head; // Return the head of the modified list
}

int main(){

    linkedList ll;
    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(3);
    ll.insertAtTail(4);
    ll.insertAtTail(5);
    
    cout<<"Original List: ";
    ll.display();

    int n = 2;
    ll.head = removeNthFromEnd(ll.head,n);
    
    cout<<"List after removing "<<n<<"th node from end: ";
    ll.display();

    return 0;
}