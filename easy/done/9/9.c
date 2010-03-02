#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int data[100001];
int datb[100001];


int check (int n)
{
    int i;

    for (i = 0; i < n; i++)
        datb[data[i]-1] = i+1;

    if (!memcmp (datb, data, sizeof (int) * n))
        return 1;
    else
        return 0;
}



int main(int argc, char *argv[])
{
    int n, i;

    while (1) {
        scanf ("%d", &n);
        if (!n)
            break;

        for (i = 0; i < n; i++)
            scanf ("%d", data+i);

        if (check (n))
            printf ("ambiguous\n");
        else
            printf ("not ambiguous\n");
    }
    return 0;
}

