#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int c;
    int w;
    int m;
} dest_t;


typedef struct {
    int total;
    int c;
    int w;
    int m;
} src_t;


/*
  constraints:
  1. res_c + res_w + res_m <= cap
  2. res_c <= (res_w+res_m)*4
  3. res_w <= res_m*2 
  
  targets:
  max res_c -> max res_w -> max res_m
 */
void solve (src_t* src, dest_t* dest)
{
    int i;

    dest->c = dest->w = dest->m = 0;

    for (i = 0; i < src->total; i++) {
        if (dest->c < 4*(dest->w + dest->m) && dest->c < src->c)
            dest->c++;
        else
            if (dest->w < 2*dest->m && dest->w < src->w)
                dest->w++;
            else
                if (dest->m < src->m)
                    dest->m++;
    }
}


int main (int argc, char *argv[])
{
    int t;
    src_t src;
    dest_t dest;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d %d %d %d", &src.total, &src.m, &src.w, &src.c);
        
        solve (&src, &dest);
        printf ("%d %d %d\n", dest.m, dest.w, dest.c);
    }

    return 0;
}
