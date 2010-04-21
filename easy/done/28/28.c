#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int pts[600][2];
int pts_count;
char plane[500][500];


inline void set_pt_plane (int x, int y)
{
    plane[x+200][y+200] = 1;
}


inline char pt_plane (int x, int y)
{
    return plane[x+200][y+200];
}


inline int square (int p1, int p2)
{
    int x3, y3, x4, y4;

    x3 = pts[p1][0] - (pts[p2][1] - pts[p1][1]);
    y3 = pts[p1][1] + (pts[p2][0] - pts[p1][0]);
    x4 = pts[p2][0] - (pts[p2][1] - pts[p1][1]);
    y4 = pts[p2][1] + (pts[p2][0] - pts[p1][0]);

    return pt_plane (x3, y3) && pt_plane (x4, y4);
}


int solve ()
{
    int res = 0, i, j;

    for (i = 0; i < pts_count; i++)
        for (j = i+1; j < pts_count; j++) {
            if (square (i, j))
                res++;
        }

    return res;
}


int pts_compare (const void* a, const void* b)
{
    const int* aa = a;
    const int* bb = b;

    if (aa[0] == bb[0])
        return aa[1] - bb[1];
    
    return aa[0] - bb[0];
}


int main(int argc, char *argv[])
{
    int t, i;

    scanf ("%d", &t);
    while (t--) {
        memset (plane, 0, sizeof (plane));

        scanf ("%d", &pts_count);
        for (i = 0; i < pts_count; i++) {
            scanf ("%d %d", pts[i]+0, pts[i]+1);
            set_pt_plane (pts[i][0], pts[i][1]);
        }

        qsort (pts, pts_count, sizeof (pts[0]), pts_compare);

        printf ("%d\n", solve () / 2);

    }
    return 0;
}
