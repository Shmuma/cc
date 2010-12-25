#include <stdio.h>
#include <stdlib.h>

void fill (char* buf, int cnt)
{
    cnt++;
    while (cnt > 0) {
        *buf = 'a' + --cnt;
        buf++;
    }
}


int main (int argc, char *argv[])
{
    int t, n, p, i, idx;
    char buf[120];

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        idx = 0;
        
        if (n % 25) {
            fill (buf, n % 25);
            idx = 1+(n % 25);
            n -= idx-1;
        }
        while ((int)(n / 25) > 0) {
            fill (buf+idx, 25);
            idx += 26;
            n -= 25;
        }
        buf[idx] = 0;
        puts (buf);
    }
    return 0;
}
