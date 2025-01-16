/*
Next Greater Element 1 - [Leetcode-496(Easy)]
================================================

The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.

You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

Example 1:
22
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Brute Force Approach
vector<int>findNextGreaterElement(vector<int>& nums1 , vector<int>& nums2){
    /*
    * Time: O(n^2);
    */ 
    vector<int>ans;  // creating a empty vector to store ans array.

    // Iterate over each element in nums1
    for(int i=0;i<nums1.size();i++){
        
        // find => It is a standard library function that is used to find an element in a range (from the beginning to the end of a sequence, such as an array or a vector).
        int idx = find(nums2.begin(),nums2.end(),nums1[i])-nums2.begin();

        // flag will be used to check if a next greater element is found
        int flag = 0;

        // Iterate over the elements in nums2 starting from the index x (found in step 3) to the end of nums2.
        for(int j=idx;j<nums2.size();j++){

            // Check if the current element nums2[j] is greater than the current element 
            if(nums2[j] > nums1[i] && flag == 0){

                // If the condition is true then set the flag to 1 & add current element 'nums2[j]' to the ans vector.
                flag = 1;
                ans.push_back(nums2[j]);
            }
        }
        // If the flag is still 0 after the inner loop, it means no next greater element was found for the current element in nums1. In this case, add -1 to the result vector ans.
        if(flag == 0) ans.push_back(-1);
    }
    return ans;
}

int main(){

    int m;
    cout<<"Enter the size of 1st vector: ";
    cin>>m;

    vector<int>vec1(m);
    cout<<"Enter the elements of 1st vector: ";
    for(int i=0;i<m;i++){
        cin>>vec1[i];
    }

    int n;
    cout<<"Enter the size of 2nd vector: ";
    cin>>n;

    vector<int>vec2(n);
    cout<<"Enter the elements of 2nd vector: ";
    for(int i=0;i<n;i++){
        cin>>vec2[i];
    }

    vector<int>ans = findNextGreaterElement(vec1,vec2);
    cout<<"Next Greater Element for each element in 1st vector is: ";
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }

    return 0;
}