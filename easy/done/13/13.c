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
            switch (bit) {
            case 0:
                printf ("2(0)");
                break;
            case 1:
                printf ("2");
                break;
            default:
                printf ("2(");
                show (bit);
                printf (")");
                break;
            }
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
        if (scanf ("%d", &n) <= 0)
            break;
        printf ("%d=", n);
        show (n);
        putchar ('\n');
    }
    return 0;
}
