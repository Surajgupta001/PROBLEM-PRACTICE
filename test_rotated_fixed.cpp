#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Corrected version
int rotatedDigits(int n)
{
    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        string s = to_string(i);
        bool isValid = true;
        bool hasRotatingDigit = false;

        for (auto digit : s)
        {
            // Check if digit is invalid (3, 4, 7 cannot be rotated)
            if (digit == '3' or digit == '4' or digit == '7')
            {
                isValid = false;
                break;
            }

            // Check if digit is rotating (2, 5, 6, 9)
            if (digit == '2' or digit == '5' or digit == '6' or digit == '9')
            {
                hasRotatingDigit = true;
            }
        }

        // Count only if all digits are valid AND at least one is rotating
        if (isValid and hasRotatingDigit)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    cout << "n=10: " << rotatedDigits(10) << " (expected: 4)" << endl;
    cout << "n=1: " << rotatedDigits(1) << " (expected: 0)" << endl;
    cout << "n=2: " << rotatedDigits(2) << " (expected: 1)" << endl;
    cout << "n=22: " << rotatedDigits(22) << " (expected: 13)" << endl;
    cout << "n=26: " << rotatedDigits(26) << " (expected: 14)" << endl;
    return 0;
}
