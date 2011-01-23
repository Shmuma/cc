#include <stdio.h>
#include <stdlib.h>

int table[] = {1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};


int main(int argc, char *argv[])
{
    int t, sum;
    char c;

    scanf ("%d", &t);
    getchar ();
    while (t--) {
        sum = 0;
        while ((c = getchar ()) != '\n')
            sum += table[c-'A'];
        printf ("%d\n", sum);
    }
    return 0;
}
