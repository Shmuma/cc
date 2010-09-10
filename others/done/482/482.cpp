#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF 102400

unsigned int perm[BUF];
int count;
char* data[BUF];


int lookup (int n)
{
    for (int i = 0; i < count; i++)
        if (perm[i] == n)
            return i;
}



int main ()
{
    int i, n, ofs, data_ofs, first = 1;
    unsigned int v;
    char buf[1024000], *p;
    char val[1024];

    scanf ("%d", &n);
    getchar ();

    while (n--) {
        getchar ();
        count = 0;

        while (1) {
            scanf ("%u", &v);
            perm[v-1] = count++;
            if (getchar () == '\n')
                break;
        }

        scanf ("%[^\n]", buf);
        getchar ();

        p = buf;
        data_ofs = 0;

        while (*p) {
            ofs = 0;
            while (*p && *p != ' ')
                val[ofs++] = *(p++);
            if (*p)
                p++;
            val[ofs] = 0;
            data[data_ofs++] = strdup (val);
        }
        
        if (!first)
            printf ("\n");
        first = 0;

        for (i = 0; i < count; i++) {
            printf ("%s\n", data[perm[i]]);
        }

        for (i = 0; i < count; i++)
            free (data[i]);
    }

    return 0;
}

// 0:43.79
// 0:20.33
