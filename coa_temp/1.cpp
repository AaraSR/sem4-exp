#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Convert decimal to binary (2's complement)
vector<int> decimalToBinary(int number, int bits)
{
    vector<int> binary(bits, 0);

    if (number < 0)
        number = (1 << bits) + number;

    for (int i = bits - 1; i >= 0; i--)
    {
        binary[i] = number % 2;
        number /= 2;
    }

    return binary;
}

// Convert binary to decimal (2's complement)
long long binaryToDecimal(vector<int> binary)
{
    int bits = binary.size();
    long long decimal = 0;

    if (binary[0] == 0)
    {
        for (int i = 0; i < bits; i++)
            decimal = decimal * 2 + binary[i];
    }
    else
    {
        long long value = 0;
        for (int i = 0; i < bits; i++)
            value = value * 2 + binary[i];
        decimal = value - (1LL << bits);
    }

    return decimal;
}

// Binary addition
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

// 2's complement
vector<int> twosComplement(vector<int> binary)
{
    int n = binary.size();

    for (int i = 0; i < n; i++)
        binary[i] = (binary[i] == 0) ? 1 : 0;

    vector<int> one(n, 0);
    one[n - 1] = 1;

    return addBinary(binary, one);
}

// Arithmetic Right Shift (A, Q, Q-1)
void arithmeticRightShift(vector<int>& A, vector<int>& Q, int &Q_1)
{
    int n = A.size();

    Q_1 = Q[n - 1];

    for (int i = n - 1; i > 0; i--)
        Q[i] = Q[i - 1];

    Q[0] = A[n - 1];

    int sign = A[0];

    for (int i = n - 1; i > 0; i--)
        A[i] = A[i - 1];

    A[0] = sign;
}

// Print binary
void printBinary(vector<int> binary)
{
    for (int i = 0; i < binary.size(); i++)
        cout << binary[i];
}

int main()
{
    int multiplicand, multiplier;

    cout << "Enter Multiplicand (Decimal): ";
    cin >> multiplicand;

    cout << "Enter Multiplier (Decimal): ";
    cin >> multiplier;

    // Calculate required bits dynamically
    int maxValue = max(abs(multiplicand), abs(multiplier));
    int bits = 0;

    while (maxValue > 0)
    {
        maxValue /= 2;
        bits++;
    }

    bits += 2;  // extra safety bits
    int n = bits;

    vector<int> M = decimalToBinary(multiplicand, n);
    vector<int> Q = decimalToBinary(multiplier, n);
    vector<int> A(n, 0);
    int Q_1 = 0;

    vector<int> minusM = twosComplement(M);

    // Booth's Algorithm
    for (int i = 0; i < n; i++)
    {
        if (Q[n - 1] == 1 && Q_1 == 0)
            A = addBinary(A, minusM);
        else if (Q[n - 1] == 0 && Q_1 == 1)
            A = addBinary(A, M);

        arithmeticRightShift(A, Q, Q_1);
    }

    // Combine A and Q
    vector<int> result = A;
    result.insert(result.end(), Q.begin(), Q.end());

    long long decimalResult = binaryToDecimal(result);

    cout << "\nMultiplicand (M) = " << multiplicand << " = ";
    printBinary(decimalToBinary(multiplicand, n));

    cout << "\nMultiplier (Q) = " << multiplier << " = ";
    printBinary(decimalToBinary(multiplier, n));

    cout << "\n\nProduct (Binary) = ";
    printBinary(result);

    cout << "\nProduct (Decimal) = " << decimalResult << endl;

    return 0;
}