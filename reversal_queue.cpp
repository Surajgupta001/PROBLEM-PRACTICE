#include <iostream>
#include <stack>
#include <queue>
using namespace std;

queue<int>reverseQueue(queue<int>qu){
    
    stack<int>st;
    while(!qu.empty()){
        st.push(qu.front());
        qu.pop();
    }
    while(!st.empty()){
        qu.push(st.top());
        st.pop();
    }
    return qu;
}

int main(){

    queue<int>qu;
    qu.push(10);
    qu.push(20);
    qu.push(30);
    qu.push(40);
    qu.push(50);
    
    qu = reverseQueue(qu);
    cout<<"Reversed Queue: ";
    while(!qu.empty()){
        cout<<qu.front()<<" ";
        qu.pop();
    }
    cout<<endl;

    return 0;
}