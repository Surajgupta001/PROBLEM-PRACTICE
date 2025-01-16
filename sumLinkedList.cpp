/*
You are given two non-empty linked list representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the numbers and return the sum as linked list.

INPUT |1: [2,4,3]  INPUT |2: [5,6,4]
OUTPUT: [7,0,8]

INPUT |1: [9,9,9,9,9,9,9] INPUT |2: [9,9,9,9]
OUPUT: [8,9,9,9,0,0,0,1]
*/ 
#include <iostream>
using namespace std;

class node{
    public:
    int value;
    node *next;

    node(int data){
        value = data;
        next = nullptr;
    }
};

class LinkedList{
    public:
    node *head;

    LinkedList(){
        head = nullptr;
    }

    // insert AT Tail
    void insert(int data){
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
            cout << temp->value<< " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

LinkedList addTwoNumbers(LinkedList l1, LinkedList l2){
    LinkedList result;
    node *temp1 = l1.head;
    node *temp2 = l2.head;

    int carry = 0;

    while(temp1 != nullptr || temp2 != nullptr){

        int sum = carry;

        if(temp1 != nullptr){
            sum = sum + temp1->value;
            temp1 = temp1->next;
        }
        if(temp2 != nullptr){
            sum = sum + temp2->value;
            temp2 = temp2->next;
        }

        carry = sum / 10;
        result.insert(sum % 10);
    }

    if(carry > 0){
        result.insert(carry);
    }

    return result;
}

int main(){
    LinkedList l1, l2, result;
    l1.insert(2);
    l1.insert(4);
    l1.insert(3);

    l2.insert(5);
    l2.insert(6);
    l2.insert(4);

    result = addTwoNumbers(l1, l2);
    result.display();

    LinkedList l3, l4, result2;
    l3.insert(9);
    l3.insert(9);
    l3.insert(9);
    l3.insert(9);
    l3.insert(9);
    l3.insert(9);
    l3.insert(9);

    l4.insert(9);
    l4.insert(9);
    l4.insert(9);
    l4.insert(9);

    result2 = addTwoNumbers(l3, l4);
    result2.display();

    return 0;
}