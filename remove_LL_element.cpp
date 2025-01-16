/*
Remove Linked List Elements - [Leetcode - 203(Easy)]
======================================================

Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.

Example 1:

Input: head = [1,2,6,3,4,5,6], k = 6
Output: [1,2,3,4,5]

Example 2:

Input: head = [], k = 1
Output: []

Example 3:

Input: head = [7,7,7,7], k = 7
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

class Linkedlist{
    public:
    node *head;

    // constructor
    Linkedlist(){
        head = nullptr;
    }

    void insertion(int data){
        node *new_node = new node(data);
        if(head == nullptr){
            head = new_node;
            return; 
        }
        node *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = new_node;
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

node *removeElement(node *head, int k){
    // step 1: if head is null
    if(head == nullptr){
        return head;
    }

    // step 2: Remove nodes with value k from the beginning of the list
    while(head != nullptr && head->value == k){
        head = head->next;
    }

    // step 3: creating a pointer to traverse the list
    node *curr = head;

    // step 4: traverse the list and remove nodes with value k
    while(curr != nullptr && curr->next != nullptr){
        if(curr->next->value == k){
            curr->next = curr->next->next;
        }
        else{
            curr = curr->next;
        }
    }

    // step 5: return the head
    return head;
}
int main(){

    Linkedlist list;
    cout<<"Original List: ";
    list.insertion(1);
    list.insertion(2);
    list.insertion(6);
    list.insertion(4);
    list.insertion(5);
    list.insertion(6);
    list.display();


    int k;
    cout<<"Enter the value to remove: ";
    cin>>k;

    cout<<"After removed value: ";
    list.head = removeElement(list.head, k);
    list.display();

    return 0;
}