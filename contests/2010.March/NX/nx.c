#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NDEBUG


float build[150][2];
int build_count;

/* safe area */
float xs, ys, rs;


void solve ();


int main(int argc, char *argv[])
{
    int n, i;

    scanf ("%d", &n);
    while (n--) {
        scanf ("%f %f %f", &xs, &ys, &rs);
        scanf ("%d", &build_count);
        for (i = 0; i < build_count; i++)
            scanf ("%f %f", &build[i][0], &build[i][1]);
        
        solve ();
    }

    return 0;
}


void circum (int p1, int p2, int p3, float *x, float *y, float *r)
{
    float d, px, py;
    float a, b, c;

    d = 2 * (build[p1][0] * (build[p2][1] - build[p3][1]) +
             build[p2][0] * (build[p3][1] - build[p1][1]) +
             build[p3][0] * (build[p1][1] - build[p2][1]));

    a = build[p1][0] * build[p1][0] + build[p1][1] * build[p1][1];
    b = build[p2][0] * build[p2][0] + build[p2][1] * build[p2][1];
    c = build[p3][0] * build[p3][0] + build[p3][1] * build[p3][1];

    px = (a * (build[p2][1] - build[p3][1]) +
          b * (build[p3][1] - build[p1][1]) +
          c * (build[p1][1] - build[p2][1]));

    py = (a * (build[p3][0] - build[p2][0]) +
          b * (build[p1][0] - build[p3][0]) +
          c * (build[p2][0] - build[p1][0]));
    
    *x = (float)px / (float)d;
    *y = (float)py / (float)d;
    *r = sqrt ((build[p1][0] - *x) * (build[p1][0] - *x) + (build[p1][1] - *y) * (build[p1][1] - *y));
}

float dist (float x1, float y1, float x2, float y2)
{
    return sqrt ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int is_safe (float x, float y)
{
    return (x-xs)*(x-xs) + (y-ys)*(y-ys) < rs*rs;
}

/* sum of squared distance between circle and  */
float distance (float x, float y, float r)
{
    int i;
    float res = 0, f;

    for (i = 0; i < build_count; i++) {
        f = dist (build[i][0], build[i][1], x, y) - r;
        res += f*f;
    }

    return res;
}


void solve ()
{
    int i, j, k;
    float x, y, r;
    int comp = 0;
    float min_dist, dst;
    float b_x, b_y, b_r;

    for (i = 0; i < build_count; i++)
        for (j = i+1; j < build_count; j++)
            for (k = j+1; k < build_count; k++) {
                circum (i, j, k, &x, &y, &r);
                if (is_safe (x, y)) {
                    dst = distance (x, y, r);
#ifdef DEBUG
                    printf ("%.3f %.3f %.3f -> %.3f\n", x, y, r, dst);
#endif
                    if (!comp || dst < min_dist) {
                        min_dist = dst;
                        b_x = x;
                        b_y = y;
                        b_r = r;
                        comp = 1;
                    }

                }
            }

#ifdef DEBUG
    printf ("Best: %.3f %.3f %.3f -> %.3f\n", b_x, b_y, b_r, min_dist);
#endif
    printf ("%.3f %.3f %.3f\n", b_x, b_y, b_r);
}
