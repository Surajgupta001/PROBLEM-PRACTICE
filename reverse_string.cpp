#include <iostream>
#include <vector>
#include <string>
using namespace std;

void reverseString(vector<char>&v){
    /*
    * Time: O(n);
    * Space: O(n);
    */ 
    int i = 0;
    int j = v.size()-1;
    
    while(i < j){
        swap(v[i++], v[j--]);
    }
}

int main(){

    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    vector<char> ch(str.begin(), str.end());
    reverseString(ch);

    for(char c : ch){
        cout << c;
    }
    cout << endl;

    return 0;
}

/* ================================================= */ 

#include <iostream>
#include <string>
using namespace std;

void reverseString(string& str) {
    /*
    * Time: O(n);
    * Space: O(1)
    */
    int i = 0;
    int j = str.size() - 1;
    while (i < j) {
        swap(str[i++], str[j--]);
    }
}

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    reverseString(str);

    cout << "Reversed string: " << str << endl;

    return 0;
}