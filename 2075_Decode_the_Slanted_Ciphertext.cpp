/*
Decode the Slanted Ciphertext - [Leetcode - 2075]
-----------------------------------------------------
A string originalText is encoded using a slanted transposition cipher to a string encodedText with the help of a matrix having a fixed number of rows rows.

originalText is placed first in a top-left to bottom-right manner.


The blue cells are filled first, followed by the red cells, then the yellow cells, and so on, until we reach the end of originalText. The arrow indicates the order in which the cells are filled. All empty cells are filled with ' '. The number of columns is chosen such that the rightmost column will not be empty after filling in originalText.

encodedText is then formed by appending all characters of the matrix in a row-wise fashion.


The characters in the blue cells are appended first to encodedText, then the red cells, and so on, and finally the yellow cells. The arrow indicates the order in which the cells are accessed.

For example, if originalText = "cipher" and rows = 3, then we encode it in the following manner:


The blue arrows depict how originalText is placed in the matrix, and the red arrows denote the order in which encodedText is formed. In the above example, encodedText = "ch ie pr".

Given the encoded string encodedText and number of rows rows, return the original string originalText.

Note: originalText does not have any trailing spaces ' '. The test cases are generated such that there is only one possible originalText.

Example 1:

Input: encodedText = "ch   ie   pr", rows = 3
Output: "cipher"
Explanation: This is the same example described in the problem description.

Example 2:


Input: encodedText = "iveo    eed   l te   olc", rows = 4
Output: "i love leetcode"
Explanation: The figure above denotes the matrix that was used to encode originalText. 
The blue arrows show how we can find originalText from encodedText.

Example 3:


Input: encodedText = "coding", rows = 1
Output: "coding"
Explanation: Since there is only 1 row, both originalText and encodedText are the same.
 

Constraints:

0 <= encodedText.length <= 10^6
encodedText consists of lowercase English letters and ' ' only.
encodedText is a valid encoding of some originalText that does not have trailing spaces.
1 <= rows <= 1000
The testcases are generated such that there is only one possible originalText.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Approach-1 (Simple simulation with extra space)
//T.C : O(l), l = encodedText.length()
//S.C : O(l), all characters of encodedText in matrix
string decodeCiphertext(string encodedText, int rows) {
    int l       = encodedText.size();
    int columns = l / rows;
    
    string originalText;
    
    for (int col = 0; col < columns; col++) {
        for (int j = col; j < l; j += (columns + 1)) {
            originalText += encodedText[j];
        }
    }
    
    //Remove spaces put at the end
    while (!originalText.empty() && originalText.back() == ' ') {
        originalText.pop_back();
    }
    
    return originalText;
}

string decodeCiphertext(string encodedText, int rows) {
    if (rows == 1)  return encodedText;
    
    int l       = encodedText.size();
    int columns = l / rows;
    
    string originalText = "";
    
    //Create matrix
    vector<vector<char>> mat(rows, vector<char>(columns));
    
    int idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            mat[i][j] = encodedText[idx++];
        }
    }
    
    //Read diagonally
    for (int col = 0; col < columns; col++) {
        int i = 0;
        int j = col;
        while (i < rows && j < columns) {
            originalText += mat[i][j];
            i++;
            j++;
        }
    }
    
    // Step 3: Remove trailing spaces
    while (!originalText.empty() && originalText.back() == ' ') {
        originalText.pop_back();
    }
    
    return originalText;
}

//Approach-2 (Without extra space)
//T.C : O(l), l = encodedText.length()
//S.C : O(1)
string decodeCiphertext(string encodedText, int rows) {
    int l = encodedText.length();
    int columns = l / rows;
    
    string originalText;
    
    for(int col = 0; col < columns; col++) {
        for(int j = col; j < l; j += (columns+1)) {
            originalText += encodedText[j];
        }
    }
    
    while(!originalText.empty() && originalText.back() == ' ') {
        originalText.pop_back();
    }
    
    return originalText;
}


int main() {
    string encodedText1 = "ch   ie   pr";
    int rows1 = 3;
    cout << "Original Text (Example 1): " << decodeCiphertext(encodedText1, rows1) << endl; // Output: "cipher"

    string encodedText2 = "iveo    eed   l te   olc";
    int rows2 = 4;
    cout << "Original Text (Example 2): " << decodeCiphertext(encodedText2, rows2) << endl; // Output: "i love leetcode"

    string encodedText3 = "coding";
    int rows3 = 1;
    cout << "Original Text (Example 3): " << decodeCiphertext(encodedText3, rows3) << endl; // Output: "coding"

    return 0;
}