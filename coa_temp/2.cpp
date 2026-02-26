// nonrestoring_division.cpp
// Simple, beginner-friendly implementation of Non-Restoring Division.
// For clarity this version handles integer division (signed) using bit logic.
// It uses magnitude (absolute values) and applies sign at the end.

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

int main() {
    cout << "Non-Restoring Division (simple integer version)\n";
    int dividend_input, divisor_input;
    cout << "Enter dividend (integer): ";
    cin >> dividend_input;
    cout << "Enter divisor (integer, non-zero): ";
    cin >> divisor_input;
    if (divisor_input == 0) {
        cout << "Divisor cannot be zero.\n";
        return 1;
    }

    // Save sign and work with absolute values for the algorithm
    bool resultNegative = ( (dividend_input < 0) ^ (divisor_input < 0) );
    int64_t dividend = llabs((int64_t)dividend_input);
    int64_t divisor  = llabs((int64_t)divisor_input);

    // If dividend is 0 quickly return
    if (dividend == 0) {
        cout << "Quotient = 0, Remainder = 0\n";
        return 0;
    }

    // Determine number of bits needed to represent dividend
    int nbits = 0;
    int64_t temp = dividend;
    while (temp > 0) { temp >>= 1; ++nbits; }
    if (nbits == 0) nbits = 1;

    // remainder starts at 0, quotient bits will be filled from MSB..LSB
    int64_t remainder = 0;
    vector<int> quotientBits(nbits, 0);

    // Non-restoring division main loop
    // We process bits from MSB to LSB of the dividend
    for (int i = nbits - 1; i >= 0; --i) {
        // Left shift (remainder, bring next dividend bit into remainder)
        remainder = (remainder << 1) | ( (dividend >> i) & 1LL );

        // Non-restoring step: decide to subtract or add divisor
        if (remainder >= 0) {
            remainder = remainder - divisor; // try subtracting
        } else {
            remainder = remainder + divisor; // if negative, add divisor
        }

        // Set current quotient bit based on remainder sign
        if (remainder >= 0) quotientBits[i] = 1;
        else quotientBits[i] = 0;

        // (Optional) Uncomment to print step debug:
        // cout << "After bit " << i << ": remainder=" << remainder << " quotientBit=" << quotientBits[i] << "\n";
    }

    // Final correction: if remainder is negative, add divisor back
    if (remainder < 0) remainder += divisor;

    // Build quotient integer from bits
    int64_t quotient_magnitude = 0;
    for (int i = nbits - 1; i >= 0; --i) {
        quotient_magnitude = (quotient_magnitude << 1) | quotientBits[i];
    }

    // Apply sign
    int64_t quotient = resultNegative ? -quotient_magnitude : quotient_magnitude;
    int64_t remainder_signed = remainder; // remainder is always non-negative here

    cout << "Result:\n";
    cout << "Quotient = " << quotient << "\n";
    cout << "Remainder = " << remainder_signed << "\n";

    // Quick verification using integer division
    cout << "(Check) dividend = divisor * quotient + remainder -> "
         << (divisor_input * quotient + remainder_signed) << "\n";

    return 0;
}