#include <stdio.h>
#include <stdlib.h>


int max_n;


int solve ();

int branch_1 (int m, int n);
int branch_2 (int m, int n);
int branch_3 (int m, int n);


int main (int argc, char *argv[])
{
    int t, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        max_n = n;
        printf ("%d\n", solve ());
    }
    return 0;
}


int count (int a, int b)
{
    if (b > max_n)
        return 0;

    return 1 + count (a, a+b) + count (b, a+b);
}


int solve ()
{
    return count (1, 2);
}
