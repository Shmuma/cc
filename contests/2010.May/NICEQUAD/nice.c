#include <stdio.h>
#include <stdlib.h>


void count (int n, int* even, int* neven)
{
    if (n % 2)
        (*neven)++;
    else
        (*even)++;
}



int min (int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}


int diff_even (int even1, int neven1, int even2, int neven2)
{
    return even1*even2 + neven1*neven2;
}


int diff_neven (int even1, int neven1, int even2, int neven2)
{
    return even1*neven2 + neven1*even2;
}


int mul_even (int even1, int neven1, int even2, int neven2)
{
    return (even1 + neven1) * (even2 + neven2) - neven1 * neven2;
}


int mul_neven (int even1, int neven1, int even2, int neven2)
{
    return neven1 * neven2;
}



int main(int argc, char *argv[])
{
    int t, n, i, x, y;
    int res;

    int eax, eay, nax, nay;
    int ebx, eby, nbx, nby;
    int ecx, ecy, ncx, ncy;
    int edx, edy, ndx, ndy;
    int v[10];
    int area1_even, area1_neven;
    int area2_even, area2_neven;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &n);
        eax = eay = nax = nay = 0;
        ebx = eby = nbx = nby = 0;
        ecx = ecy = ncx = ncy = 0;
        edx = edy = ndx = ndy = 0;

        for (i = 0; i < n; i++) {
            scanf ("%d %d", &x, &y);
            if (x == 0 || y == 0)
                continue;
            if (x > 0 && y > 0) {
                count (x, &eax, &nax);
                count (y, &eay, &nay);
            }
            if (x > 0 && y < 0) {
                count (x, &ebx, &nbx);
                count (y, &eby, &nby);
            }
            if (x < 0 && y < 0) {
                count (x, &ecx, &ncx);
                count (y, &ecy, &ncy);
            }
            if (x < 0 && y > 0) {
                count (x, &edx, &ndx);
                count (y, &edy, &ndy);
            }
        }

        printf ("eax = %d, eay = %d, nax = %d, nay = %d\n", eax, eay, nax, nay);
        printf ("ebx = %d, eby = %d, nbx = %d, nby = %d\n", ebx, eby, nbx, nby);
        printf ("ecx = %d, ecy = %d, ncx = %d, ncy = %d\n", ecx, ecy, ncx, ncy);
        printf ("edx = %d, edy = %d, ndx = %d, ndy = %d\n", edx, edy, ndx, ndy);
        printf ("\n");

        v[0] = diff_even  (eax, nax, ecx, ncx);
        v[1] = diff_neven (eax, nax, ecx, ncx);
        printf ("X A-C: even: %d, neven: %d\n", v[0], v[1]);
        v[2] = diff_even  (eay, nay, eby, nby);
        v[3] = diff_neven (eay, nay, eby, nby);
        printf ("Y A-B: even: %d, neven: %d\n", v[2], v[3]);

        v[4] = mul_even  (v[0], v[1], v[2], v[3]);
        v[5] = mul_neven (v[0], v[1], v[2], v[3]);
        printf ("Mul1: even: %d, neven: %d\n\n", v[4], v[5]);

        v[10] = diff_even  (eax, nax, ebx, nbx);
        v[11] = diff_neven (eax, nax, ebx, nbx);
        printf ("X A-B: even: %d, neven: %d\n", v[10], v[11]);
        v[12] = diff_even  (eay, nay, ecy, ncy);
        v[13] = diff_neven (eay, nay, ecy, ncy);
        printf ("Y A-C: even: %d, neven: %d\n", v[12], v[13]);

        v[14] = mul_even  (v[10], v[11], v[12], v[13]);
        v[15] = mul_neven (v[10], v[11], v[12], v[13]);
        printf ("Mul2: even: %d, neven: %d\n\n", v[14], v[15]);

        area1_even  = diff_even  (v[4], v[5], v[14], v[15]);
        area1_neven = diff_neven (v[4], v[5], v[14], v[15]);
        printf ("Area1: even: %d, neven: %d\n\n", area1_even, area1_neven);

        continue;

        res = 0;
        v[0] = diff_neven (mul_even  (diff_even  (eax, nax, ecx, ncx),
                                      diff_neven (eax, nax, ecx, ncx),
                                      diff_even  (eay, nay, ecy, ncy),
                                      diff_neven (eay, nay, ecy, ncy)),
                           mul_neven (diff_even  (eax, nax, ecx, ncx),
                                      diff_neven (eax, nax, ecx, ncx),
                                      diff_even  (eay, nay, ecy, ncy),
                                      diff_neven (eay, nay, ecy, ncy)),
                           mul_even  (diff_even  (eax, nax, ebx, nbx),
                                      diff_neven (eax, nax, ebx, nbx),
                                      diff_even  (eay, nay, eby, nby),
                                      diff_neven (eay, nay, eby, nby)),
                           mul_neven (diff_even  (eax, nax, ebx, nbx),
                                      diff_neven (eax, nax, ebx, nbx),
                                      diff_even  (eay, nay, eby, nby),
                                      diff_neven (eay, nay, eby, nby)));
        v[1] = diff_neven (mul_even  (diff_even  (eax, nax, ecx, ncx),
                                      diff_neven (eax, nax, ecx, ncx),
                                      diff_even  (eay, nay, ecy, ncy),
                                      diff_neven (eay, nay, ecy, ncy)),
                           mul_neven (diff_even  (eax, nax, ecx, ncx),
                                      diff_neven (eax, nax, ecx, ncx),
                                      diff_even  (eay, nay, ecy, ncy),
                                      diff_neven (eay, nay, ecy, ncy)),
                           mul_even  (diff_even  (eax, nax, edx, ndx),
                                      diff_neven (eax, nax, edx, ndx),
                                      diff_even  (eay, nay, edy, ndy),
                                      diff_neven (eay, nay, edy, ndy)),
                           mul_neven (diff_even  (eax, nax, edx, ndx),
                                      diff_neven (eax, nax, edx, ndx),
                                      diff_even  (eay, nay, edy, ndy),
                                      diff_neven (eay, nay, edy, ndy)));
                        
        printf ("%d %d\n", v[0], v[1]);
    }

    return 0;
}
