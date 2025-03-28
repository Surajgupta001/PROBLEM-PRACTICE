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
#include <stack>
using namespace std;

class node{
    public:
    int value;
    node* next;

    node(int data){
        value = data;
        next = nullptr;
    }
};

class Linkedlist{
    public:
    node* head;

    Linkedlist(){
        head = nullptr;
    }

    void insertAtTail(int value){
        node* new_node = new node(value);
        if(head == nullptr){ // LInked list is empty
            head = new_node;
            return;
        }
        node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = new_node;
    }

    void display(){
        node* temp = head;
        while(temp != nullptr){
            cout << temp->value << "->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

bool isPalindrome(node *head){
    stack<int>st;
    node *curr = head;
    while(curr){
        st.push(curr->value);
        curr = curr->next;
    }
    curr = head;
    while(curr){
        if(curr->value != st.top()){
            return false;
        }
        st.pop();
        curr = curr->next;
    }
    return true;
}

int main() {
    Linkedlist ll;
    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(2);
    ll.insertAtTail(1);

    cout << "Linked List 1: ";
    ll.display();

    if(isPalindrome){
        cout << "Linked List is a palindrome." << endl;
    }
    else{
        cout << "Linked List is not a palindrome." << endl;
    }

    return 0;
}