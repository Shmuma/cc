#include <stdio.h>
#include <stdlib.h>


unsigned long long cache[40][40];

unsigned long long solve (int players, int capt);
unsigned long long do_solve (int left, int right);


int main ()
{
    int a, b;
    unsigned long long res;

    while (1) {
        if (scanf ("%d %d", &a, &b) != 2)
            break;

        res = solve (a, b);
        printf ("%llu\n", res);
    }

    return 0;
}



unsigned long long solve (int players, int capt)
{
    if (capt == 1)
        if (players > 3) 
            return do_solve (0, players-3);
        else
            return 1;
   
    return do_solve (players-capt, capt-1); 
}


unsigned long long do_solve (int left, int right)
{
    unsigned long long res = 0;

    if (!right)
        if (!left)
            return 1;
        else
            return 0;

    if (cache[left][right])
        return cache[left][right];

    for (int i = 0; i < right; i++)
        res += do_solve (right-i-1, left+i);

    cache[left][right] = res;
    return res;
}


