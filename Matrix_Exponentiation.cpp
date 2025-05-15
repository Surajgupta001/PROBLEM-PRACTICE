/*
Write a C++ program to compute the nth term of a linear recurrence relation using Matrix Exponentiation. The program should take the following inputs:

The size of the transformation matrix.
The transformation matrix itself (row by row).
The initial vector representing the first few terms of the recurrence relation.
The value of n for which the nth term needs to be computed.
The program should handle cases where n is smaller than the size of the initial vector and should use modular arithmetic with a modulus of (10^9 + 7) to prevent overflow. Provide the implementation and explain how the program works.

Example: 

Input:

Enter the size of the transformation matrix: 2
Enter the transformation matrix (row by row):
1 1
1 0
Enter the initial vector:
1 0
Enter the value of n to compute the nth term: 10

Output:

The nth term is: 55

Explanation:
This example computes the 10th term of the Fibonacci sequence using the transformation matrix:
[1 1]
[1 0]

and the initial vector:
[1 0], which represents the first two Fibonacci numbers. The program uses matrix exponentiation to compute the nth term efficiently.

The program is generalized and can handle any linear recurrence relation, not just Fibonacci.
*/ 

#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9 + 7;

// Generalized function to multiply two matrices
vector<vector<long long>> matrixMultiplication(vector<vector<long long>>& A, vector<vector<long long>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    vector<vector<long long>> result(rowsA, vector<long long>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] = (result[i][j] + ((long long)A[i][k] * B[k][j]) % mod) % mod;
            }
        }
    }
    return result;
}

// Function to raise matrix base to the power exponent (Just like Binary exponentiation)
vector<vector<long long>> matrixExponentiation(vector<vector<long long>>& base, long long exponent) {
    if (exponent == 0) {
        int size = base.size();
        vector<vector<long long>> identity(size, vector<long long>(size, 0));
        for (int i = 0; i < size; i++) {
            identity[i][i] = 1;
        }
        return identity;
    }

    vector<vector<long long>> half = matrixExponentiation(base, exponent / 2);
    vector<vector<long long>> result = matrixMultiplication(half, half);

    if (exponent % 2 == 1) {
        result = matrixMultiplication(result, base);
    }
    return result;
}

int main() {
    // Input: Size of the transformation matrix
    cout << "Enter the size of the transformation matrix: ";
    int size;
    cin >> size;

    // Input: Transformation matrix
    vector<vector<long long>> base(size, vector<long long>(size));
    cout << "Enter the transformation matrix (row by row):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> base[i][j];
        }
    }

    // Input: Initial vector
    vector<long long> initial(size);
    cout << "Enter the initial vector:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> initial[i];
    }

    // Input: Term to compute
    cout << "Enter the value of n to compute the nth term: ";
    long long n;
    cin >> n;

    // Base case
    if (n < size) {
        cout << "The nth term is: " << initial[n] << endl;
        return 0;
    }

    // Compute (base^(n-size+1)) using matrix exponentiation
    vector<vector<long long>> resultMatrix = matrixExponentiation(base, n - size + 1);

    // Compute the nth term by multiplying the result matrix with the initial vector
    long long nthTerm = 0;
    for (int i = 0; i < size; i++) {
        nthTerm = (nthTerm + (resultMatrix[0][i] * initial[i]) % mod) % mod;
    }

    cout << "The nth term is: " << nthTerm << endl;

    return 0;
}

/*
------- INPUTS -----
Enter the size of the transformation matrix: 2
Enter the transformation matrix (row by row):
1 1
1 0
Enter the initial vector:
1 0
Enter the value of n to compute the nth term: 10
*/ 