#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


unsigned char matrix[1001][1001];
unsigned int size;
unsigned char string[2008];

int delta[][2] = {
    { -1, -1 },
    { -1, 1 },
    { 1, -1 },
    { 1, 1 },
};


inline int check (int i, int j)
{
    if (i < 0 || j < 0 || i >= size || j >= size)
        return 0;
    return 1;
}


unsigned long long solve_substr (int i, int j, int ofs)
{
    unsigned long long res = 0;
    int d, ii, jj;

    if (!string[ofs])
        return 1;

    for (d = 0; d < sizeof (delta) / sizeof (delta[0]); d++) {
        ii = i + delta[d][0];
        jj = j + delta[d][1];
        if (check (ii, jj) && matrix[ii][jj] == string[ofs])
            res += solve_substr (ii, jj, ofs+1);
    }

    return res;
}


unsigned long long solve ()
{
    unsigned long long res = 0;
    int i, j;

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (matrix[i][j] == string[0])
                res += solve_substr (i, j, 1);

    return res;
}


unsigned char get_next ()
{
    int c;
    
    while (1) {
        c = getchar ();
        if (c < 0)
            return 0;
        if (!isspace (c))
            break;
    }

    return c;
}


int main (int argc, char *argv[])
{
    int i, j;

    scanf ("%d", &size);

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            matrix[i][j] = get_next ();

    i = 0;
    while ((string[i] = get_next ()) && i < sizeof (string))
        i++;

    printf ("%llu\n", solve ());
    
    return 0;
}
