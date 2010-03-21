#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 1


static char buf[32*1024];
static int count, pos;
static int eof;


void fetch ()
{
    int ret;

    count -= pos;
    if (count > 0 && pos > 0)
        memmove (buf, buf+pos, count);
    pos = 0;
    ret = read (0, buf+count, sizeof (buf)-count);
    if (ret < 0)
        return;
    count += ret;
    eof = count == 0;
}


inline void skip_spaces ()
{
    while (pos < count && isspace (buf[pos]))
        pos++;
}


int getnum ()
{
    int res = 0;

    do {
        if (count == pos)
            fetch ();
        skip_spaces ();
        if (eof)
            return 0;
    }
    while (count == pos);

    while (isdigit (buf[pos])) {
        res *= 10;
        res += buf[pos] - '0';
        pos++;
        if (pos == count) {
            fetch ();
            if (eof)
                break;
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    int n, t = 0;

    while (1) {
        n = getnum ();
        if (eof)
            break;
        if (n != t)
            printf ("Bug at %d, got %d\n", t, n);
        t++;
    }
    
    return 0;
}
