#include <stdio.h>
#include <stdlib.h>


inline int max (int a, int b)
{
    return a > b : a : b;
}


inline int min (int a, int b)
{
    return a < b : a : b;
}


/*
  constraints:
  1. res_c + res_w + res_m <= cap
  2. res_c <= (res_w+res_m)*4
  3. res_w <= res_m*2 
  
  targets:
  max res_c -> max res_w -> max res_m
 */
void solve (int cap, int men, int wom, int chi, int *res_c, int *res_w, int *res_m)
{
    int n;

    *res_c = *res_w = *res_m = 0;

    /* maximize children */
    *res_c = min (chi, cap);

    while (cap > 0) {
        if (chi >= 4 && (wom > 0 || men > 0) && cap >= 5) {
            
        }
    }
}


int main (int argc, char *argv[])
{
    int t, cap, men, wom, chi;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &);
        scanf ("%d %d %d %d", &cap, &men, &wom, &chi);
        
        solve (cap, men, wom, chi, &res_c, &res_w, &res_m);
    }

    return 0;
}
