/*
Palindrome Linked List(LEETCODE-234)
==========================
Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

Example 1:

Input: head = [1,2,2,1]
Output: true

Example 2:

Input: head = [1,2]
Output: false
*/ 
#include <iostream>
using namespace std;

class node{
    public:
    int value;
    node* next;

    // constructor
    node(int data){
        value = data;
        next = NULL;
    }
};

class Linkedlist{
    public:
    node* head;

    Linkedlist(){
        head = nullptr;
    }

    void insertAtTail(int value){

        node *new_node = new node(value);
        if(head == nullptr){ // linked list is empty
            head = new_node;
            return;
        }

        node *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp -> next = new_node;
    }

    void display(){
        node *temp = head;
        while(temp != nullptr){
            cout<<temp -> value <<"->";
            temp = temp -> next;
        }
        cout<<"NULL"<<endl;
    }
};

bool isPalindrome(node *head){
    
    // step-1. FIND MIDDLE ELEMENT
    node *slow = head;
    node *fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    // Now slow is pointing to middle element;
    // STEP-2. BREAK THE LINKED LIST IN THE MIDDLE
    node *curr = slow -> next;
    node *prev = slow;
    slow -> next = nullptr;

    // STEP-3. REVERSE THE SECOND HALF OF LINKED LIST
    while(curr){
        node *next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    }

    // STEP-4. CHECK IF TWO LINKED LIST ARE EQUAL
    node *head1 = head;
    node *head2 = prev;
    while(head2){
        if(head1->value != head2->value){
            return false;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    return true;
}

int main(){

    Linkedlist ll;

    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(3);
    ll.insertAtTail(3);
    ll.insertAtTail(2);
    ll.insertAtTail(1);
    ll.display();
    cout<<isPalindrome(ll.head)<<endl;

    return 0;
}