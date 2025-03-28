/*
Daily Temperature - [Leetcode - 739(Medium)]
=============================================
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]
*/ 

/*
* ===> Based on Monotonic Stack / Next Greater Element
* ===> Time Complexity: O(n)
* ===> Space Complexity: O(n)
* ===> Monotonic Stack: Monotonic stack ensures sorted elements with a strict requirement, forming increasing or decreasing stacks.
* ===> Pseudo-code involves maintaining a non-increasing sequence for efficient computation.

Conclusion:
* ===> Monotonic stack is a valuable structure for array element comparison.
* ===> The algorithm's utility is evident in solving coding constraints.
*/ 

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int>dailyTemp(vector<int>& temp){ // here temp is temperature
    // Making same size as temp
    vector<int>ans(temp.size(),0);
    stack<int> st; // stack to hold indices 
    st.push(0);
    for(int i=1;i<temp.size();i++){
        // Indices in stack and the current element temp ig greater than the temp at the index at top of the stack
        while(!st.empty() && temp[i] > temp[st.top()]){
            // Index of the day from the top of the stack
            int idx = st.top();
            st.pop();
            // Calculating the number if days to wait
            ans[idx] = i - idx; // i is the current day, idx is the day are comparing
        }
        st.push(i);
    }
    return ans;
}

int main(){
    
    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int> temp(n);
    cout<<"Enter the elements of vector: ";
    for(int i=0;i<n;i++){
        cin>>temp[i];
    }

    vector<int> ans = dailyTemp(temp);
    cout<<"Next Greater Element for each element in the vector is: ";
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }

    return 0;
}