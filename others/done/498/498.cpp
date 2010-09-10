#include <stdio.h>
#include <stdlib.h>

char buf[1024];
long long k[1024];
int count;

long long eval (long long v)
{
    long long s = 0;

    for (int i = 0; i < count; i++) {
        s *= v;
        s += k[i];
    }

    return s;
}


int main ()
{
    char* p;
    long long v, res;
    int first;

    while (1) {
        buf[0] = 0;
        if (!scanf ("%[^\n]", buf) || !buf[0])
            break;
        getchar ();

        p = buf;
        count = 0;
        while (*p) {
            sscanf (p, "%lld", k+count);
            count++;
            while (*p && *p != ' ')
                p++;
            if (*p)
                p++;
        }

        if (!scanf ("%[^\n]", buf))
            break;
        getchar ();

        first = 1;
        p = buf;
        while (*p) {
            sscanf (p, "%lld", &v);

            res = eval (v);
            if (!first)
                printf (" ");
            printf ("%lld", res);
            first = 0;

            while (*p && *p != ' ')
                p++;
            if (*p)
                p++;
        }
        printf ("\n");
    }

    return 0;
}
