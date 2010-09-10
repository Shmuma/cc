#include <stdio.h>
#include <stdlib.h>


int main ()
{
    int index = 1;
    int n, i, j, k;
    int pows[7];
    int val;
    char res[256];
    char c;

    while (1) {
        if (!scanf ("%d", &n) || !n)
            break;
        printf ("S-Tree #%d:\n", index++);
        
        for (i = 0; i < n; i++) {
            while ((c = getchar ()) != 'x');
            pows[getchar ()-'0'-1] = 1 << (n-i-1);
        }
        while ((c = getchar ()) != '\n');

        i = 0;
        while ((c = getchar ()) != '\n') {
            res[i] = c;
            i++;
        }

        scanf ("%d", &k);
        while ((c = getchar ()) != '\n');
        
        for (j = 0; j < k; j++) {
            val = 0;
            for (i = 0; i < n; i++) {
                c = getchar ();
                val += (c-'0')*pows[i];
            }
            printf ("%c", res[val]);
            while ((c = getchar ()) != '\n');
        }
        printf ("\n\n");
    }

    return 0;
}
