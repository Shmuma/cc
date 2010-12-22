#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned int digits[50];
unsigned int digits_count;

#define MAX_PRIMES 100000

unsigned int primes[MAX_PRIMES];
int primes_count;


void make_primes (int max)
{
    int val, i, max_mul, is_prime;

    primes_count = 1;
    primes[0] = 2;
    val = 3;

    while (val <= max && primes_count < MAX_PRIMES) {
        i = 0;
        max_mul = (int)sqrt (val);
        is_prime = 1;
        while (i < primes_count && primes[i] <= max_mul) {
            if ((val % primes[i]) == 0) {
                is_prime = 0;
                break;
            }
            i++;
        }

        if (is_prime)
            primes[primes_count++] = val;
        val += 2;
    }
}


int is_prime (unsigned long long n)
{
    int i;

    if (n == 1)
        return 1;

    for (i = 0; i < primes_count; i++) {
        if (n == primes[i])
            return 1;
        if ((n % primes[i]) == 0)
            return 0;
    }

    return 1;
}



void num_to_digits (unsigned long long n)
{
    digits_count = 0;
    while (n > 0) {
        digits[digits_count++] = n % 10;
        n /= 10;
    }
}


int count_digits (unsigned long long n)
{
    int res = 0;

    while (n > 0) {
        n /= 10;
        res++;
    }

    return res;
}


unsigned long long digits_to_num (unsigned int* arr, unsigned int count)
{
    int i;
    unsigned long long res = 0;

    for (i = count-1; i >= 0; i--) {
        res *= 10;
        res += arr[i];
    }

    return res;
}



unsigned long long digits_to_num_inv (unsigned int* arr, unsigned int count)
{
    int i;
    unsigned long long res = 0;

    for (i = 0; i < count; i++) {
        res *= 10;
        res += arr[i];
    }

    return res;
}



void dissect (unsigned long long n, unsigned long long* base, int* extra, unsigned long long* rest_inv, unsigned long long* base_inv)
{
    unsigned int base_count;

    num_to_digits (n);
    base_count = digits_count >> 1;

    if (digits_count % 2) {
        *base = digits_to_num (digits+(base_count+1), base_count);
        if (base_inv)
            *base_inv = digits_to_num_inv (digits+(base_count+1), base_count);
        *extra = digits[base_count];
    }
    else {
        *base = digits_to_num (digits + base_count, base_count);
        if (base_inv)
            *base_inv = digits_to_num_inv (digits + base_count, base_count);
        *extra = -1;
    }
    if (rest_inv)
        *rest_inv = digits_to_num_inv (digits, base_count);
}



unsigned long long make_palin (unsigned long long base, int extra)
{
    unsigned long long res = base;
    int i;

    if (extra >= 0) {
        res *= 10;
        res += extra;
    }

    num_to_digits (base);

    for (i = 0; i < digits_count; i++)
        res *= 10;
    return res + digits_to_num_inv (digits, digits_count);
}


void next_palin (unsigned long long* base, int* extra, int* digits)
{
    int dig;
    unsigned long long palin;

    if (*extra >= 0) {
        if (*extra == 9)
            *extra = 0;
        else {
            (*extra)++;
            return;
        }
    }

    (*base)++;
    dig = count_digits (*base);

    if (dig != *digits) {
        if (*extra < 0) {
            palin = make_palin ((*base) / 10, 0);
            dissect (palin, base, extra, NULL, NULL);
            dig = count_digits (*base);
        }
        else
            *extra = -1;
        *digits = dig;
    }
}


unsigned long long solve (unsigned long long base, int extra)
{
    int digits = count_digits (base);

    while (!is_prime (make_palin (base, extra))) {
        next_palin (&base, &extra, &digits);
    }

    return make_palin (base, extra);
}


int main (int argc, char *argv[])
{
    unsigned long long n, base, base_inv, rest_inv, palin;
    int extra;

    make_primes (1000000);

    scanf ("%llu", &n);

    dissect (n, &base, &extra, &rest_inv, &base_inv);

    if (base_inv > rest_inv)
        palin = solve (base, extra);
    else
        palin = solve (base+1, extra);

    printf ("%llu\n", palin);
    return 0;
}
