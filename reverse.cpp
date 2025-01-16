/*
Write a program to print a number in reverse order.

INPUT: num = 12345-
OUTPUT: num = -54321
*/ 
#include <iostream>
using namespace std;

void reverseNumber(int num){
    int reversedNum = 0;
    int sign = -1;
    if(num<0){
        sign = -1;
        num = -num;
    }
    while(num>0){
        int digit = num % 10;
        reversedNum = reversedNum*10 + digit;
        num = num/10;
    }
    cout<<"Reverse Order: "<<sign*reversedNum<<endl;
}
int main() {

    int num;
    cout<<"Enter a number: ";
    cin>>num;

    reverseNumber(num);

    return 0;
}
