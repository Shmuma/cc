#include <stdio.h>
#include <stdlib.h>


int w, h;
int buf[100][100];
int tmp[200][200];

void solve (int* cyc, int* max);



int main ()
{
    while (1) {
        scanf ("%d %d", &w, &h);

        if (!w && !h)
            break;

        getchar ();

        memset (buf, 0, sizeof (buf));

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
                buf[i][j] = getchar () == '/' ? 0 : 1;
            getchar ();
        }

        int cyc, max;

        solve (&cyc, &max);
    }

    return 0;
}



void solve (int* cyc, int* max)
{
    int i, j;

    for (i = 0; i < h*2; i++) {
        
    }
}
