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
    int v1, v2;

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

        res = 0;
        v1 = diff_neven (mul_even  (diff_even  (eax, nax, ecx, ncx),
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
        v2 = diff_neven (mul_even  (diff_even  (eax, nax, ecx, ncx),
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
                        
        printf ("%d %d\n", v1, v2);
    }

    return 0;
}
