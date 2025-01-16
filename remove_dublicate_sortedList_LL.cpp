/*
REMOVE DUBLICATES FROM FORM SORTED LINKEDLIST - (LEEDCODE-83) - EASY
=============================================================

Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

Example 1:

Input: head = [1,1,2]
Output: [1,2]

Example 2:

Input: head = [1,1,2,3,3]
Output: [1,2,3]

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
        next = nullptr;
    }
};

class LinkedList{
    public:
    node* head;

    // constructor
    LinkedList(){
        head = nullptr;
    }

    void insertAtTail(int data){
        node* newNode = new node(data);
        if(head == nullptr){
            head = newNode;
            return;
        }
        else{
            // traverse of linked list for Tail insertion
            node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
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

node* removeDublicate(node *head){
    node* result = head;
    while(head && head->next){
        if(head->value == head->next->value){
            head->next = head->next->next;
        }
        else{
            head = head->next;
        }
    }
    return result;
}

int main(){

    LinkedList ll;
    ll.insertAtTail(1);
    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(3);
    ll.insertAtTail(3);

    cout << "Before removing duplicates: ";
    ll.display();

    ll.head = removeDublicate(ll.head);

    cout << "After removing duplicates: ";
    ll.display();

    return 0;
}