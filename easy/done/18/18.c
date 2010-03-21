#include <stdio.h>
#include <stdlib.h>


int getnum (int a)
{
    int c;
    int n = 0;

    do {
        c = getchar_unlocked ();
    }
    while (c < '0' || c > '9');

    while (c >= '0' && c <= '9') {
        n = n * 10 + c-'0';
        if (n > a)
            n %= a;
        c = getchar_unlocked ();
    }

    return n;
}


int gcd (int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd (b, a % b);
}


void copy ()
{
    int c;

    do {
        c = getchar_unlocked ();
    }
    while (c < '0' || c > '9');

    while (c >= '0' && c <= '9') {
        putchar_unlocked (c);
        c = getchar_unlocked ();
    }
}


int main(int argc, char *argv[])
{
    int n, a, b;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &a);
        getchar ();
        if (a > 0) {
            b = getnum (a);
            printf ("%d\n", gcd (a, b));
        }
        else {
            copy ();
            putchar_unlocked ('\n');
        }
    }

    return 0;
}
