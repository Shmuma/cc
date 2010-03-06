#include <stdio.h>
#include <stdlib.h>


void show (int n)
{
    int flag = 1;
    int bit = 15;

    if (n == 0)
        return;

    if (n == 1) {
        printf ("2(0)");
        return;
    }

    if (n == 2) {
        printf ("2");
        return;
    }

    while (n > 0) {
        if ((1 << bit) & n) {
            if (!flag)
                putchar ('+');
            printf ("2(");
            show (bit);
            printf (")");
            flag = 0;
            n ^= 1 << bit;
        }
        bit--;
    }
}


int main(int argc, char *argv[])
{
    int n;

    while (1) {
        scanf ("%d", &n);
        show (n);
        putchar ('\n');
    }
    return 0;
}
