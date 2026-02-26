#include <iostream>
#include <vector>
using namespace std;

// Function to convert integer to binary (fixed number of bits)
vector<int> decimalToBinary(int number, int bits)
{
    vector<int> binary(bits, 0);

    // If number is negative, convert to 2's complement
    if (number < 0)
    {
        number = (1 << bits) + number;
    }

    for (int i = bits - 1; i >= 0; i--)
    {
        binary[i] = number % 2;
        number = number / 2;
    }

    return binary;
}

// Function to convert binary to decimal (2's complement)
int binaryToDecimal(vector<int> binary)
{
    int bits = binary.size();
    int decimal = 0;

    // If MSB is 0 -> positive number
    if (binary[0] == 0)
    {
        for (int i = 0; i < bits; i++)
        {
            decimal = decimal * 2 + binary[i];
        }
    }
    else // negative number
    {
        int value = 0;
        for (int i = 0; i < bits; i++)
        {
            value = value * 2 + binary[i];
        }
        decimal = value - (1 << bits);
    }

    return decimal;
}

// Function to add two binary numbers
vector<int> addBinary(vector<int> A, vector<int> B)
{
    int n = A.size();
    vector<int> result(n, 0);
    int carry = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        int sum = A[i] + B[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    return result;
}

// Function to find 2's complement
vector<int> twosComplement(vector<int> binary)
{
    int n = binary.size();

    // 1's complement
    for (int i = 0; i < n; i++)
    {
        binary[i] = (binary[i] == 0) ? 1 : 0;
    }

    // add 1
    vector<int> one(n, 0);
    one[n - 1] = 1;

    return addBinary(binary, one);
}

// Function to print binary number
void printBinary(vector<int> binary)
{
    for (int i = 0; i < binary.size(); i++)
    {
        cout << binary[i];
    }
}

int main()
{
    int dividend, divisor;

    cout << "Enter Dividend (Q): ";
    cin >> dividend;

    cout << "Enter Divisor (M): ";
    cin >> divisor;

    if (divisor == 0)
    {
        cout << "Division by zero not allowed.";
        return 0;
    }

    int bits = 5;   // fixed 5 bits (works for example 7/3)
    int n = bits;

    // Load dividend into A and Q (2n bits concept)
    vector<int> Q = decimalToBinary(dividend, n);
    vector<int> M = decimalToBinary(divisor, n);
    vector<int> A(n, 0);   // initially A = 0

    cout << "\nInitial Values:\n";
    cout << "A = "; printBinary(A);
    cout << "  Q = "; printBinary(Q);
    cout << "  M = "; printBinary(M);
    cout << "\n\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Step " << i + 1 << ":\n";

        // Step 2: Shift left (A,Q)
        A.erase(A.begin());
        A.push_back(Q[0]);

        Q.erase(Q.begin());
        Q.push_back(0);

        cout << "After Shift Left -> A = ";
        printBinary(A);
        cout << "  Q = ";
        printBinary(Q);
        cout << endl;

        vector<int> A_before = A;   // Save old A

        // Step 3: If A and M same sign, A = A - M
        // Otherwise A = A + M
        if (A[0] == M[0])
        {
            vector<int> minusM = twosComplement(M);
            A = addBinary(A, minusM);  // A = A - M
            cout << "A = A - M\n";
        }
        else
        {
            A = addBinary(A, M);       // A = A + M
            cout << "A = A + M\n";
        }

        cout << "After Operation -> A = ";
        printBinary(A);
        cout << endl;

        // Step 4: Check success
        if (A[0] == A_before[0])
        {
            Q[n - 1] = 1;
            cout << "Operation Successful -> Q0 = 1\n";
        }
        else
        {
            Q[n - 1] = 0;
            A = A_before;   // Restore
            cout << "Operation Unsuccessful -> Q0 = 0 and A Restored\n";
        }

        cout << "Now A = ";
        printBinary(A);
        cout << "  Q = ";
        printBinary(Q);
        cout << "\n\n";
    }

    int quotient = binaryToDecimal(Q);
    int remainder = binaryToDecimal(A);

    // Step 6: Sign correction
    if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
    {
        Q = twosComplement(Q);
        quotient = binaryToDecimal(Q);
    }

    cout << "Final Result:\n";
    cout << "Quotient (Binary) = ";
    printBinary(Q);
    cout << "\nRemainder (Binary) = ";
    printBinary(A);

    cout << "\n\nQuotient (Decimal) = " << quotient;
    cout << "\nRemainder (Decimal) = " << remainder << endl;

    return 0;
}