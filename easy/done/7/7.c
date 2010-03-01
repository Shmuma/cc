#include <stdio.h>
#include <stdlib.h>


int lines;
int data[100][100];


int solve ()
{
    int i, j;

    for (i = lines-2; i >= 0; i--) {
        for (j = 0; j <= i; j++)
            if (data[i+1][j] > data[i+1][j+1])
                data[i][j] += data[i+1][j];
            else
                data[i][j] += data[i+1][j+1];
    }

    return data[0][0];
}


int main(int argc, char *argv[])
{
    int n, i, j;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &lines);
        for (i = 0; i < lines; i++) {
            for (j = 0; j < i+1; j++)
                scanf ("%d", &data[i][j]);
        }

        printf ("%d\n", solve ());
    }

    return 0;
}
