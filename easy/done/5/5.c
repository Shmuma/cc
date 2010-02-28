#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRIES 30

int table[101][ENTRIES];



void multiply (int num, int val)
{
    int i = 0, rem = 0;

    for (i = 0; i < ENTRIES; i++) {
        table[num][i] *= val;
        table[num][i] += rem;
        rem = table[num][i] / 1000000;
        table[num][i] %= 1000000;
    }
}


void calc_table ()
{
    int i;

    table[1][0] = 1;
    
    for (i = 2; i <= 100; i++) {
        memcpy (table[i], table[i-1], sizeof (table[i]));
        multiply (i, i);
    }
}


void show_number (int n)
{
    int i, flag = 0;

    for (i = ENTRIES - 1; i >= 0; i--) {
        if (flag)
            printf ("%06d", table[n][i]);
        else {
            if (table[n][i]) {
                flag = 1;
                printf ("%d", table[n][i]);
            }
        }
    }
    putchar ('\n');
}


int main(int argc, char *argv[])
{
    int t, n;

    calc_table ();

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &n);
        show_number (n);
    }

    return 0;
}
