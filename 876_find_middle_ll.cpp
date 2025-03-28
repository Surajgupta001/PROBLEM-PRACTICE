/*
Pattern: Slow and fast pointer

MIDDLE OF LINKED LIST - (LEETCODE - 876)
Given the head of a singly linked list, return the middle node of the linked list.

If there are two middle nodes, return the second middle node.

Example 1:

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Example 2:

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

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

class Linkedlist{
    public:
    node *head;

    // constructor
    Linkedlist(){
        head = nullptr;
    }

    void insertAtTail(int value){
        node* newNode = new node(value);
        if(head == nullptr){ // linked list is empty
            head = newNode;
            return;
        }
        else{
            node *temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
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

// 1st APPROCH
node *findMiddleElement(node *&head){
    /*
    * TIME: O(n);
    * SPACE: O(1);
    */ 
    node *slow = head;
    node *fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 2nd APPROCH
// node *findMiddleElement(node *head){
//     /*
//     * TIME: O(n);
//     * SPACE: O(1);
//     */ 
//     int count = 0;
//     node *temp = head;

//     // count the number of nodes in the the linked list
//     while(temp != nullptr){
//         count++;
//         temp = temp->next;
//     }
//     temp = head;
//     for(int i=0;i<count/2;i++){
//         temp = temp->next;
//     }
//     return temp;
// }

int main(){
    Linkedlist ll;

    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(3);
    ll.insertAtTail(4);
    ll.insertAtTail(5);
    ll.insertAtTail(6);

    ll.display();

    node *middleNode = findMiddleElement(ll.head);

    cout<<"Middle element of linked list is: "<<middleNode->value<<endl;

    return 0;
}