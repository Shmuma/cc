#include <stdio.h>
#include <stdlib.h>


unsigned int digits[50];
unsigned int digits_count;


void num_to_digits (unsigned long long n)
{
    digits_count = 0;
    while (n > 0) {
        digits[digits_count++] = n % 10;
        n /= 10;
    }
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
        *base_inv = digits_to_num_inv (digits+(base_count+1), base_count);
        *extra = digits[base_count];
    }
    else {
        *base = digits_to_num (digits + base_count, base_count);
        *base_inv = digits_to_num_inv (digits + base_count, base_count);
        *extra = -1;
    }
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



unsigned long long solve (unsigned long long base, int extra)
{
    int i;

    for (i = 0; i < 100; i++)
        printf ("%llu\n", make_palin (base+i, extra));

    return make_palin (base, extra);
}


int main (int argc, char *argv[])
{
    unsigned long long n, base, base_inv, rest_inv, palin;
    int extra;

    scanf ("%llu", &n);

    dissect (n, &base, &extra, &rest_inv, &base_inv);

    if (base_inv > rest_inv)
        palin = solve (base, extra);
    else
        palin = solve (base+1, extra);

    printf ("%llu\n", palin);
    return 0;
}
