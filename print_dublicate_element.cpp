/*
Print Duplicate Element in given array, else return -1.

INPUT: arr = [0,5,8,9]
OUTPUT: -1.

INPUT: arr = [0,1,1,2,2,8,3,9]
OUTPUT: 1,2. 
*/ 
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void printDuplicateElement(vector<int>&v){
    /*
    * Time: O(n)
    * Space: O(1)
    */ 
    unordered_map<int, int>freq;
    for(int i=0;i<v.size();i++){
        freq[v[i]]++;
    }
    
    bool hasDuplicate = false;
    for(auto itr = freq.begin(); itr!= freq.end(); itr++){
        if(itr->second > 1){
            cout<<itr->first<<" ";
            hasDuplicate = true;
        }
    }
    
    if(!hasDuplicate){
        cout<<-1;
    }
}

int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    printDuplicateElement(v);

    return 0;
}


/* ============================================= */ 
#include <iostream>
#include <vector>
using namespace std;

void printDuplicateElement(vector<int>&v){
    /*
    * Time: O(n^2)
    * Space: O(1)
    */ 
    bool hasDuplicate = false;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i] == v[j]){
                cout<<v[i]<<" ";
                hasDuplicate = true;
                break;
            }
        }
    }
    
    if(!hasDuplicate){
        cout<<-1;
    }
}

int main(){
    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    printDuplicateElement(v);

    return 0;
}