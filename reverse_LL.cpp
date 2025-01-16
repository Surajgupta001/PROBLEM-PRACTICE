/*
Reverse Linked List - [Leetcode - 206(Easy)]
============================================
Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:

Input: head = [1,2]
Output: [2,1]
Example 3:

Input: head = []
Output: []
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

    // insertion from tail
    void insert(int data){
        node *new_node = new node(data);
        if(head == nullptr){
            head = new_node;
            return;
        }
        else{
            node *temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new_node;
        }
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

// Reversing Linked List
node* reverseLinkedList(node* &head){
    node *prev_ptr = nullptr;
    node *curr_ptr = head;

    // curr_ptr->next = prev_ptr;
    // move all 3 ptrs by one step ahead
    // repeat this process until curr_ptr != nullptr
    while(curr_ptr != nullptr){
        node *next_ptr = curr_ptr->next;
        curr_ptr->next = prev_ptr;

        // update the Link of Linked List 
        prev_ptr = curr_ptr;
        curr_ptr = next_ptr;
    }

    // when this loop ends, prev_ptr pointing to my last node is new node
    node *new_head = prev_ptr;
    return new_head;
}

int main(){
    LinkedList ll;

    cout<<"Inserting elements in Linked Lists are: "<<endl;
    ll.insert(1);
    ll.insert(2);
    ll.insert(3);
    ll.insert(4);
    ll.insert(5);
    ll.display();

    cout<<"Reversing Linked Lists are: "<<endl;
    ll.head = reverseLinkedList(ll.head);
    ll.display();

    return 0;
}