// booth_multiplication.cpp
// Simple, beginner-friendly implementation of Booth's algorithm.
// Uses bit vectors (two's complement) to simulate registers.

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

// Helper: turn an integer into nbits two's complement bit vector (MSB at index 0)
vector<int> intToTwosComplementBits(int64_t value, int nbits) {
    vector<int> bits(nbits, 0);
    // handle negative values by mapping into unsigned range modulo 2^nbits
    uint64_t mask = (nbits >= 64) ? ~0ULL : ((1ULL << nbits) - 1ULL);
    uint64_t uvalue = static_cast<int64_t>(value) & mask;
    for (int i = nbits - 1; i >= 0; --i) {
        bits[i] = (uvalue & 1ULL) ? 1 : 0;
        uvalue >>= 1;
    }
    return bits;
}

// Helper: add two n-bit binary vectors (two's complement addition), return n-bit result
vector<int> addBits(const vector<int>& a, const vector<int>& b) {
    int n = (int)a.size();
    vector<int> sum(n, 0);
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int s = a[i] + b[i] + carry;
        sum[i] = s & 1;
        carry = (s >> 1) & 1;
    }
    // discard final carry (overflow in fixed-width two's complement)
    return sum;
}

// Helper: two's complement negation of an n-bit vector
vector<int> negateBits(const vector<int>& bits) {
    int n = (int)bits.size();
    vector<int> inverted(n);
    for (int i = 0; i < n; ++i) inverted[i] = bits[i] ? 0 : 1; // bitwise NOT
    // add 1
    vector<int> one(n, 0);
    one[n - 1] = 1;
    return addBits(inverted, one);
}

// Convert two's complement bit vector (MSB index 0) to signed integer (64-bit)
int64_t bitsToSignedInt(const vector<int>& bits) {
    int n = (int)bits.size();
    // If MSB is 0 -> positive number
    if (bits[0] == 0) {
        uint64_t value = 0;
        for (int i = 0; i < n; ++i) value = (value << 1) | bits[i];
        return static_cast<int64_t>(value);
    } else {
        // negative: compute value - 2^n
        uint64_t value = 0;
        for (int i = 0; i < n; ++i) value = (value << 1) | bits[i];
        uint64_t mod = (n >= 64) ? 0 : (1ULL << n);
        // value is unsigned representation, convert to signed via value - 2^n
        return static_cast<int64_t>(value - (mod));
    }
}

// Arithmetic right shift on [A, Q, qMinus1] (A and Q are n-bit vectors)
// qMinus1 is a single bit stored by reference.
void arithmeticRightShift(vector<int>& A, vector<int>& Q, int& qMinus1) {
    int n = (int)A.size();
    // sign bit (A's MSB) repeats
    int sign_bit = A[0];
    // bit that will become new qMinus1 is Q's LSB
    int new_qMinus1 = Q.back();

    // shift Q right: Q[i] = Q[i-1], Q[0] = A's LSB
    for (int i = (int)Q.size() - 1; i >= 1; --i) Q[i] = Q[i - 1];
    Q[0] = A.back();

    // shift A right arithmetically: A[i] = A[i-1], A[0] = sign_bit
    for (int i = (int)A.size() - 1; i >= 1; --i) A[i] = A[i - 1];
    A[0] = sign_bit;

    qMinus1 = new_qMinus1;
}

int main() {
    cout << "Booth's Multiplication (simple bit-vector simulation)\n";
    int multiplicand, multiplier;
    cout << "Enter multiplicand (integer): ";
    cin >> multiplicand;
    cout << "Enter multiplier (integer): ";
    cin >> multiplier;

    // Determine minimal bit width needed (add 1 for sign)
    int maxAbs = max(abs(multiplicand), abs(multiplier));
    int bits = 1; // at least 1 bit
    while ((1 << (bits - 1)) <= maxAbs && bits < 31) ++bits;
    // Ensure we have an extra bit for safety/sign
    bits += 1;

    // Create bit-vectors for M (multiplicand), Q (multiplier), A (accumulator), q-1
    vector<int> M = intToTwosComplementBits(multiplicand, bits);
    vector<int> Q = intToTwosComplementBits(multiplier, bits);
    vector<int> A(bits, 0);
    int qMinus1 = 0;

    cout << "\nUsing " << bits << " bits for each register.\n";
    // Print initial registers (optional)
    auto printBits = [](const vector<int>& v) {
        for (int b : v) cout << b;
    };
    cout << "Initial M: "; printBits(M); cout << '\n';
    cout << "Initial Q: "; printBits(Q); cout << '\n';
    cout << "Initial A: "; printBits(A); cout << '\n';
    cout << "Initial q-1: " << qMinus1 << "\n\n";

    // Precompute -M for subtraction
    vector<int> minusM = negateBits(M);

    // Booth's steps: repeat bits times
    for (int step = 0; step < bits; ++step) {
        // Check Q's LSB and qMinus1
        int q0 = Q.back();
        if (q0 == 1 && qMinus1 == 0) {
            // 10 -> A = A - M  (i.e. add -M)
            A = addBits(A, minusM);
        } else if (q0 == 0 && qMinus1 == 1) {
            // 01 -> A = A + M
            A = addBits(A, M);
        }
        // Arithmetic right shift on [A Q q-1]
        arithmeticRightShift(A, Q, qMinus1);

        // Debug: print the registers after this step
        cout << "Step " << (step + 1) << ": A = ";
        printBits(A);
        cout << "  Q = ";
        printBits(Q);
        cout << "  q-1 = " << qMinus1 << '\n';
    }

    // The final result bits are concatenation A followed by Q (2*bits)
    // Create a combined bit vector for conversion (MSB at index 0)
    vector<int> resultBits;
    resultBits.insert(resultBits.end(), A.begin(), A.end());
    resultBits.insert(resultBits.end(), Q.begin(), Q.end());

    // Convert resultBits (two's complement of length 2*bits) to signed integer
    // We'll reuse bitsToSignedInt by calling it on the big vector.
    // But our helper expects up to 64 bits; ensure we don't exceed 64 bits.
    if ((int)resultBits.size() > 63) {
        cout << "\nResult bit-length > 63, can't convert safely to 64-bit integer here.\n";
        cout << "Result bits: ";
        printBits(resultBits);
        cout << "\n";
    } else {
        // Convert vector<int> to integer
        uint64_t unsignedValue = 0;
        for (int b : resultBits) {
            unsignedValue = (unsignedValue << 1) | (b ? 1ULL : 0ULL);
        }
        // If top bit (sign) is 1, convert to signed by subtracting 2^(2*bits)
        int totalBits = (int)resultBits.size();
        int64_t signedResult;
        if (resultBits[0] == 0) {
            signedResult = static_cast<int64_t>(unsignedValue);
        } else {
            uint64_t mod = (totalBits >= 64) ? 0 : (1ULL << totalBits);
            signedResult = static_cast<int64_t>(unsignedValue - mod);
        }

        cout << "\nFinal binary result (A then Q): ";
        printBits(resultBits);
        cout << "\nDecimal result = " << signedResult << '\n';
    }

    return 0;
}