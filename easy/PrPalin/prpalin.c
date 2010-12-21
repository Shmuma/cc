#include <stdio.h>
#include <stdlib.h>


unsigned int digits[50];
unsigned int digits_count;


void num_to_digits (int n)
{
    digits_count = 0;
    while (n > 0) {
        digits[digits_count++] = n % 10;
        n /= 10;
    }
}


int next_palindrome ()
{
    int i, n;
    int flag = 0

    for (i = 0; ; i++) {
        n = digits_count - i - 1;
        if (i >= n)
            break;
        if (digits[i] > digits[n]) {
            digits[n] = digits[i];
            flag = 1;
            break;
        }
        if (digits[i] < digits[n])
    }
}


unsigned long long solve (int n)
{
    num_to_digits (n);
    next_palindrome ();

    return n;
}


int main (int argc, char *argv[])
{
    int n;

    scanf ("%d", &n);

    printf ("%u\n", solve (n));
    return 0;
}
