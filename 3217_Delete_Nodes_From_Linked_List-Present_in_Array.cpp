/*
Delete Nodes From Linked List Present in Array - [LeetCode - 3217(Medium)]
---------------------------------------------------------------------------
You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.

Example 1:

Input: nums = [1,2,3], head = [1,2,3,4,5]

Output: [4,5]

Explanation:

Remove the nodes with values 1, 2, and 3.

Example 2:

Input: nums = [1], head = [1,2,1,2,1,2]

Output: [2,2,2]

Explanation:

Remove the nodes with value 1.

Example 3:

Input: nums = [5], head = [1,2,3,4]

Output: [1,2,3,4]

Explanation:



No node has value 5.

 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
All elements in nums are unique.
The number of nodes in the given list is in the range [1, 105].
1 <= Node.val <= 105
The input is generated such that there is at least one node in the linked list that has a value not present in nums.
*/ 

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

class node {
public:
    int value;
    node *next;

    // Constructor
    node(int data){
        value = data;
        next = nullptr;
    }
};

node* modifiedList(vector<int>& nums, node* head) {
    unordered_set<int> st(nums.begin(), nums.end());

    // Handle the head
    while(head != nullptr && st.find(head->value) != st.end()) {
        node* temp = head;
        head = head->next;
        delete(temp); // delete the hanging node -> dangling pointer
    }

    // Handle the rest of the list
    node* curr = head;
    while(curr != nullptr && curr->next != nullptr) {
        if(st.find(curr->next->value) != st.end()) {
            node* temp = curr->next;
            curr->next = curr->next->next;
            delete(temp); // delete the hanging node -> dangling pointer
        } else {
            curr = curr->next;
        }
    }

    return head;
}

int main() {
    // Example usage:
    vector<int> nums = {1, 2, 3};
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    node* modifiedHead = modifiedList(nums, head);

    // Print the modified list
    node* curr = modifiedHead;
    while (curr != nullptr) {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;

    return 0;
}