/*
Design Task Manager - [Leetcode - 3408(Medium)]
------------------------------------------------
There is a task management system that allows users to manage their tasks, each associated with a priority. The system should efficiently handle adding, modifying, executing, and removing tasks.

Implement the TaskManager class:

TaskManager(vector<vector<int>>& tasks) initializes the task manager with a list of user-task-priority triples. Each element in the input list is of the form [userId, taskId, priority], which adds a task to the specified user with the given priority.

void add(int userId, int taskId, int priority) adds a task with the specified taskId and priority to the user with userId. It is guaranteed that taskId does not exist in the system.

void edit(int taskId, int newPriority) updates the priority of the existing taskId to newPriority. It is guaranteed that taskId exists in the system.

void rmv(int taskId) removes the task identified by taskId from the system. It is guaranteed that taskId exists in the system.

int execTop() executes the task with the highest priority across all users. If there are multiple tasks with the same highest priority, execute the one with the highest taskId. After executing, the taskId is removed from the system. Return the userId associated with the executed task. If no tasks are available, return -1.

Note that a user may be assigned multiple tasks.

Example 1:

Input:
["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
[[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]

Output:
[null, null, null, 3, null, null, 5]

Explanation

TaskManager taskManager = new TaskManager([[1, 101, 10], [2, 102, 20], [3, 103, 15]]); // Initializes with three tasks for Users 1, 2, and 3.
taskManager.add(4, 104, 5); // Adds task 104 with priority 5 for User 4.
taskManager.edit(102, 8); // Updates priority of task 102 to 8.
taskManager.execTop(); // return 3. Executes task 103 for User 3.
taskManager.rmv(101); // Removes task 101 from the system.
taskManager.add(5, 105, 15); // Adds task 105 with priority 15 for User 5.
taskManager.execTop(); // return 5. Executes task 105 for User 5.
 

Constraints:

1 <= tasks.length <= 105
0 <= userId <= 105
0 <= taskId <= 105
0 <= priority <= 109
0 <= newPriority <= 109
At most 2 * 105 calls will be made in total to add, edit, rmv, and execTop methods.
The input is generated such that taskId will be valid.
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class TaskManager {
public:
    // Maps to store task information
    unordered_map<int, int> taskPriorityMap; // taskId -> current priority
    unordered_map<int, int> taskOwnerMap;    // taskId -> userId
    priority_queue<pair<int, int>> maxHeap;  // {priority, taskId} - max heap for highest priority
    
    // Constructor: Initialize with given tasks
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &task : tasks) {
            add(task[0], task[1], task[2]); // userId, taskId, priority
        }
    }
    
    // Add a new task to the system
    void add(int userId, int taskId, int priority) { // O(log n)
        maxHeap.push({priority, taskId});   // Add to priority queue
        taskPriorityMap[taskId] = priority; // Store current priority
        taskOwnerMap[taskId] = userId;      // Store task owner
    }
    
    // Edit the priority of an existing task
    void edit(int taskId, int newPriority) { // O(log n)
        maxHeap.push({newPriority, taskId}); // Add new priority to heap (lazy deletion)
        taskPriorityMap[taskId] = newPriority; // Update current priority
    }
    
    // Remove a task from the system
    void rmv(int taskId) {
        taskPriorityMap[taskId] = -1; // Mark as removed (lazy deletion)
    }
    
    // Execute the highest priority task
    int execTop() {
        while(!maxHeap.empty()) {
            // Get the highest priority task
            pair<int, int> top = maxHeap.top();
            maxHeap.pop();

            // k stale entries
            // O(n * log n) in worst case if all entries are stale
            
            int priority = top.first;  // Extract priority
            int taskId = top.second;   // Extract taskId
            
            // Check if this is the current valid priority for the task
            if(taskPriorityMap[taskId] == priority) {
                taskPriorityMap[taskId] = -1; // Mark as executed/removed
                return taskOwnerMap[taskId];  // Return the userId
            }
            // If not valid (old priority or removed task), continue to next
        }
        return -1; // No valid tasks to execute
    }
};

int main() {
    // Test the TaskManager
    vector<vector<int>> tasks = {{1, 101, 10}, {2, 102, 20}, {3, 103, 15}};
    TaskManager taskManager(tasks);
    
    taskManager.add(4, 104, 5);   // Add task 104 with priority 5 for user 4
    taskManager.edit(102, 8);     // Update task 102 priority to 8
    cout << taskManager.execTop() << endl; // Output: 3 (executes task 103)
    taskManager.rmv(101);         // Remove task 101
    taskManager.add(5, 105, 15);  // Add task 105 with priority 15 for user 5
    cout << taskManager.execTop() << endl; // Output: 5 (executes task 105)
    
    return 0;
}