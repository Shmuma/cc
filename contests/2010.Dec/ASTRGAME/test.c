#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int len[50];
char dic[50][50];
int dic_size;


int solve (char* s)
{
    char str[64];
    int i, j, steps, best = 0;
    char* p;

    for (i = 0; i < dic_size; i++) {
        strcpy (str, s);
        p = strstr (str, dic[i]);
        if (!p)
            continue;

        memset (p, ' ', len[i]);
        steps = solve (str);
        if (steps % 2 == 0)
            return steps+1;
        else
            best = steps+1;
    }

    return best;
}


int main (int argc, char *argv[])
{
    int n, i;
    char str[64];

    scanf ("%d", &n);
    while (n--) {
        scanf ("%s", str);
        scanf ("%d", &dic_size);
        for (i = 0; i < dic_size; i++) {
            scanf ("%s", dic[i]);
            len[i] = strlen (dic[i]);
            getchar ();
        }

        if (solve (str) % 2 == 0)
            puts ("Tracy");
        else
            puts ("Teddy");
    }

    return 0;
}
