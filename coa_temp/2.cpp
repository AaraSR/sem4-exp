#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Convert decimal to binary (fixed bits)
vector<int> decimalToBinary(int number, int bits)
{
    vector<int> binary(bits, 0);

    if (number < 0)
        number = (1 << bits) + number;   // 2's complement

    for (int i = bits - 1; i >= 0; i--)
    {
        binary[i] = number % 2;
        number /= 2;
    }

    return binary;
}

// Convert binary vector to decimal (2's complement)
int binaryToDecimal(vector<int> binary)
{
    int bits = binary.size();
    int decimal = 0;

    if (binary[0] == 0)
    {
        for (int i = 0; i < bits; i++)
            decimal = decimal * 2 + binary[i];
    }
    else
    {
        int value = 0;
        for (int i = 0; i < bits; i++)
            value = value * 2 + binary[i];
        decimal = value - (1 << bits);
    }

    return decimal;
}

// Add two binary numbers
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

// Find 2's complement
vector<int> twosComplement(vector<int> binary)
{
    int n = binary.size();

    for (int i = 0; i < n; i++)
        binary[i] = (binary[i] == 0) ? 1 : 0;

    vector<int> one(n, 0);
    one[n - 1] = 1;

    return addBinary(binary, one);
}

// Print binary
void printBinary(vector<int> binary)
{
    for (int i = 0; i < binary.size(); i++)
        cout << binary[i];
}

int main()
{
    int choice;
    cout << "Enter the Choice: (1) Decimal Numbers OR (2) Binary Numbers: ";
    cin >> choice;

    int dividendDecimal = 0, divisorDecimal = 0;
    vector<int> Q, M;

    if (choice == 1)
    {
        cout << "Enter Dividend (in Decimal): ";
        cin >> dividendDecimal;

        cout << "Enter Divisor (in Decimal): ";
        cin >> divisorDecimal;
    }
    else if (choice == 2)
    {
        string dividendBinary, divisorBinary;

        cout << "Enter Dividend (in Binary): ";
        cin >> dividendBinary;

        cout << "Enter Divisor (in Binary): ";
        cin >> divisorBinary;

        int n = max(dividendBinary.length(), divisorBinary.length());

        Q.resize(n);
        M.resize(n);

        for (int i = 0; i < n; i++)
        {
            Q[i] = dividendBinary[i] - '0';
            M[i] = divisorBinary[i] - '0';
        }

        dividendDecimal = binaryToDecimal(Q);
        divisorDecimal = binaryToDecimal(M);
    }

    else {
        cout << "Invalid choice! Exiting...\n";
        return 0;
    }

    if (divisorDecimal == 0)
    {
        cout << "Division by zero not allowed.";
        return 0;
    }

    // Dynamically calculate required bits
    int maxValue = max(abs(dividendDecimal), abs(divisorDecimal));
    int bits = 0;

    while (maxValue > 0)
    {
        maxValue /= 2;
        bits++;
    }

    bits += 2;   // extra safety bits
    int n = bits;

    Q = decimalToBinary(dividendDecimal, n);
    M = decimalToBinary(divisorDecimal, n);
    vector<int> A(n, 0);

    // Restoring Division Algorithm
    for (int i = 0; i < n; i++)
    {
        // Shift left (A,Q)
        A.erase(A.begin());
        A.push_back(Q[0]);

        Q.erase(Q.begin());
        Q.push_back(0);

        vector<int> A_before = A;

        // If A and M same sign → A = A - M
        if (A[0] == M[0])
        {
            vector<int> minusM = twosComplement(M);
            A = addBinary(A, minusM);
        }
        else
        {
            A = addBinary(A, M);
        }

        // Check success
        if (A[0] == A_before[0])
            Q[n - 1] = 1;
        else
        {
            Q[n - 1] = 0;
            A = A_before;
        }
    }

    int quotientDecimal = binaryToDecimal(Q);
    int remainderDecimal = binaryToDecimal(A);

    // Sign correction
    if ((dividendDecimal < 0 && divisorDecimal > 0) ||
        (dividendDecimal > 0 && divisorDecimal < 0))
    {
        Q = twosComplement(Q);
        quotientDecimal = binaryToDecimal(Q);
    }

    cout << "\nDividend (Q) = " << dividendDecimal << " = ";
    printBinary(decimalToBinary(dividendDecimal, n));

    cout << "\nDivisor (M) = " << divisorDecimal << " = ";
    printBinary(decimalToBinary(divisorDecimal, n));

    cout << "\n\nQuotient (Binary) = ";
    printBinary(Q);

    cout << "\nRemainder (Binary) = ";
    printBinary(A);

    cout << "\n\nQuotient (Decimal) = " << quotientDecimal;
    cout << "\nRemainder (Decimal) = " << remainderDecimal << "\n";

    return 0;
}