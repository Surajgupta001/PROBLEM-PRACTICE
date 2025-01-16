/*
You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.
Return the head of the modified linked list.

INPUT: head = [0,3,1,0,4,5,2,0] 
OUTPUT: [4,11]
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

    void insertTail(int value){
        node *new_node = new node(value);
        // if linked list is empty
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
            cout<<temp->value<<"->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
};

int main(){
    LinkedList list;
    list.insertTail(0);
    list.insertTail(3);
    list.insertTail(1);
    list.insertTail(0);
    list.insertTail(4);
    list.insertTail(5);
    list.insertTail(2);
    list.insertTail(0);
    list.display();

    return 0;
}