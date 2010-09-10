#include <stdio.h>
#include <stdlib.h>

char* data[] = {
    "0",
    "1",
    "22",
    "333",
    "4444",
    "55555",
    "666666",
    "7777777",
    "88888888",
    "999999999"
};


int main ()
{
    int n, a, b, i, j;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d %d", &a, &b);

        while (b--) {
            for (i = 0; i < a; i++)
                puts (data[i+1]);

            for (i = a-2; i >= 0; i--)
                puts (data[i+1]);

            if (b > 0)
                printf ("\n");
        }

        if (n > 0)
            printf ("\n");
    }

    return 0;
}
