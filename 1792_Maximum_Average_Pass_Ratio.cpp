/*
Maximum Average Pass Ratio - [Leetcode - 1792(Medium)] - Good Problems
-----------------------------------------------------------------------
There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.

You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.

The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.

Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.

Example 1:

Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
Output: 0.78333
Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
Example 2:

Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
Output: 0.53485
 

Constraints:

1 <= classes.length <= 105
classes[i].length == 2
1 <= passi <= totali <= 105
1 <= extraStudents <= 105
 
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//Approach-1 : (Chossing class with max delta/improvement everytime) - Will give TLE/MLE
//T.C : O(extraStudents * n)
//S.C : O(n)

/*
    Why normal Greedy fails ?
    Assigning extra students to the class with the least passing ratio assumes that improving the worst-performing class will maximize the overall average.
    However, this ignores the fact that the rate of improvement (or marginal gain) varies depending on the current number of passing and total students
    in the class. A class with a low passing ratio might require many additional students to see a significant improvement in its passing ratio,
    while a class with a higher passing ratio might see a much larger improvement with the same number of extra students.
*/

double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    int n = classes.size();
    vector<double> passRation(n);
    for(int i = 0; i < n; i++) {
        double ratio = (double)classes[i][0]/classes[i][1];
        passRation[i] = ratio;
    }
    while(extraStudents--) { //O(n)
        //student 0
        vector<double> updatedPassRation(n);
        for(int i = 0; i < n; i++) {
            double newRatio = (double)(classes[i][0]+1)/(classes[i][1]+1);
            updatedPassRation[i] = newRatio;
        }
        int bestClassIdx = 0;
        double bestDelta = 0;
        for(int i = 0; i < n; i++) { //O(n)
            double delta = updatedPassRation[i] - passRation[i];
            if(delta > bestDelta) {
                bestDelta = delta;
                bestClassIdx = i;
            }
        }
        passRation[bestClassIdx] = updatedPassRation[bestClassIdx];
        classes[bestClassIdx][0]++;
        classes[bestClassIdx][1]++;
    }
    double result = 0.0; //AR
    for(int i = 0; i < n; i++) {
        result += passRation[i];
    }
    return result/n;
}

///Approach-2 : (Chossing class with max delta/improvement everytime - Improving with max heap)
//T.C : O(extraStudents * log(n))
//S.C : O(n)
// #define P pair<double, int>
double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    int n = classes.size();
    
    priority_queue<pair<double, int>> pq; //max-heap  -  //{max-delta, idx}
    
    for(int i = 0; i < n; i++) {
        double current_PassRation = (double)classes[i][0]/classes[i][1];
        double new_PassRation = (double)(classes[i][0]+1)/(classes[i][1]+1);
        double delta = new_PassRation - current_PassRation;
        pq.push({delta, i});
    }
    
    //O(extraStudents * log(n))
    while(extraStudents--) { //O(k)
        auto curr = pq.top(); //log(n)
        pq.pop();
        
        double delta = curr.first;
        int idx = curr.second;
        
        classes[idx][0]++; //increment total passing students in the class
        classes[idx][1]++; //increment total students in the class
        
        double current_passRatio = (double)classes[idx][0]/classes[idx][1];
        double new_passRatio = (double)(classes[idx][0]+1)/(classes[idx][1]+1);
        
        delta = new_passRatio - current_passRatio;
        pq.push({delta, idx}); //log(n)
    }
    
    double result = 0.0;
    
    for(int i = 0; i < n; i++) {
        result += (double)classes[i][0]/classes[i][1];
    }
    
    return result/n;
}

int main(){
    vector<vector<int>> classes = {{1,2},{3,5},{2,2}};
    int extraStudents = 2;
    double result = maxAverageRatio(classes, extraStudents);
    cout << "Maximum Average Pass Ratio: " << result << endl;

    return 0;
}