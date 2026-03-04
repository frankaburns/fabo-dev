#include <stdio.h>

/**
 * Calculates base raised to the power of exponent using Pingala's (binary exponentiation) algorithm.
 * Assumes a non-negative integer exponent.
 */
long long pingala_power(long long base, int exponent) {
    // Base case: any number to the power of 0 is 1
    if (exponent == 0) {
        return 1;
    }

    // If exponent is even: a^n = (a^(n/2))^2
    if (exponent % 2 == 0) {
        long long half_power = pingala_power(base, exponent / 2);
        return half_power * half_power;
    } 
    // If exponent is odd: a^n = a * (a^((n-1)/2))^2 
    // Note: exponent / 2 is the same as floor(exponent / 2) for integers
    else {
        long long half_power = pingala_power(base, exponent / 2);
        return base * half_power * half_power;
    }
}

int main() {
    long long base = 2;
    int exponent = 10;
    long long result = pingala_power(base, exponent);
    printf("%lld^%d = %lld\n", base, exponent, result); // Output: 2^10 = 1024

    base = 3;
    exponent = 5;
    result = pingala_power(base, exponent);
    printf("%lld^%d = %lld\n", base, exponent, result); // Output: 3^5 = 243
    
    return 0;
}
