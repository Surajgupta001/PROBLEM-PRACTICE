#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rotatedDigits(int n)
{
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        string s = to_string(i);
        bool isvalid = true;
        for (auto str : s)
        {
            if (str == '3' or str == '4' or str == '7')
            {
                isvalid = false;
                break;
            }
            if (str == '2' or str == '5' or str == '6' or str == '9')
            {
                isvalid = true;
                count++;
            }
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
