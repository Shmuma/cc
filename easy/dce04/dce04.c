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


int add_c (src_t* src, dest_t* dest);
int add_w (src_t* src, dest_t* dest);
int add_m (src_t* src, dest_t* dest);


int finish (src_t* src)
{
    /* ther are no place on ship */
    if (!src->total)
        return 1;
    /* we placed all people */
    if (!src->c && !src->w && !src->m)
        return 1;
    return 0;
}


/* add one children */
int add_c (src_t* src, dest_t* dest)
{
    if (!src->c || !src->total)
        return 0;
    src->c--;
    src->total--;
    dest->c++;

    if (((dest->c + 3) >> 2) > (dest->w + dest->m)) {
        /* we need an adult to be placed */
        if (!add_w (src, dest))
            if (!add_m (src, dest)) {
                /* rollback */
                src->c++;
                src->total++;
                dest->c--;
                return 0;
            }
    }

    return 1;
}


/* add an woman */
int add_w (src_t* src, dest_t* dest)
{
    if (!src->w || !src->total)
        return 0;

    src->w--;
    src->total--;
    dest->w++;

    if (((dest->w+1) >> 1) > dest->m) {
        if (!add_m (src, dest)) {
            src->w++;
            src->total++;
            dest->w--;
            return 0;
        }
    }

    return 1;
}


int add_m (src_t* src, dest_t* dest)
{
    if (!src->m || !src->total)
        return 0;

    src->m--;
    src->total--;
    dest->m++;
    return 1;
}

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
    dest->c = dest->w = dest->m = 0;

    while (1) {
        if (!add_c (src, dest))
            if (!add_w (src, dest))
                if (!add_m (src, dest))
                    break;
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
