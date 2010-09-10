#include <stdio.h>
#include <stdlib.h>


int age (int d1, int m1, int y1, int d2, int m2, int y2);
int jdn (int d, int m, int y);


int main ()
{
    int n, c = 1;
    int d1, m1, y1;
    int d2, m2, y2;
    int s1, s2;
    int a;

    scanf ("%d", &n);
    
    while (n--) {
        scanf ("%d", &d1);
        getchar ();
        scanf ("%d", &m1);
        getchar ();
        scanf ("%d", &y1);

        scanf ("%d", &d2);
        getchar ();
        scanf ("%d", &m2);
        getchar ();
        scanf ("%d", &y2);

        s1 = jdn (d1, m1, y1);
        s2 = jdn (d2, m2, y2);

        printf ("Case #%d: ", c++);

        a = age (d1, m1, y1, d2, m2, y2);

        if (s1 < s2)
            printf ("Invalid birth date\n");
        else 
            if (a > 130)
                printf ("Check birth date\n");
            else
                printf ("%d\n", a);
    }

    return 0;
}


int age (int d1, int m1, int y1, int d2, int m2, int y2)
{
    int p1, p2, res;

    p1 = d1+m1*31;
    p2 = d2+m2*31;

    res = y1-y2-1;
    if (p1 >= p2)
        res++;
    return res;
}


int jdn (int d, int m, int y)
{
    if (m < 3) {
        m += 12;
        y--;
    }

    return d + (153 * m - 457) / 5 + 365 * y + y / 4 + 1721116.5;
}
