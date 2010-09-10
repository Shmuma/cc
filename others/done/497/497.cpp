#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int alt[102400];
int l[102400];
int p[102400];
int count;


void sol (int *len, int* end);
void print (int i);

int main ()
{
    int n, r, hit, first = 1;
    char buf[200];
    int len, end;

    scanf ("%d", &n);
    r = getchar ();
    r = getchar ();

    while (n--) {
        if (!first)
            printf ("\n");
        count = first = 0;

        while (1) {
            buf[0] = 0;
            scanf ("%[^\n]", buf);
            r = getchar ();
            if (!buf[0])
                break;
            sscanf (buf, "%d", alt+count);
            count++;
        }

        if (!count) 
            printf ("Max hits: 0\n");
        else {
            sol (&len, &end);
            printf ("Max hits: %d\n", len);
            print (end);
        }
    }

    return 0;
}



void sol (int *len, int *end)
{
    int i;

    *len = 1;
    *end = 0;

    for (i = 0; i < count; i++) {
        l[i] = 1;
        p[i] = -1;
        for (int j = 0; j < i; j++) {
            if (alt[i] > alt[j])
                if (l[i] < l[j]+1) {
                    l[i] = l[j]+1;
                    p[i] = j;
                }
        }
        if (l[i] > *len) {
            *len = l[i];
            *end = i;
        }
    }
}


void print (int i)
{
    if (p[i] >= 0)
        print (p[i]);
    printf ("%d\n", alt[i]);
}
