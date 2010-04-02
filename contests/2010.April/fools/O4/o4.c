#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    int t;
    int x, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d %d", &x, &n);
        
        if ((n % 2) == 0)
            printf ("%d 0\n", x);
        else {
            printf ("0 %d\n", -x);
        }
            
    }
    return 0;
}
