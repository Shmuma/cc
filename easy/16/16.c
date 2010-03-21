#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 0


static char buf[32*1024];
static int count, pos;
static int eof;


int next (int stalks, int leaves)
{
    if (leaves > stalks)
        return -1;
    
    stalks -= leaves;
    return stalks << 1;
}


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


void skip_spaces ()
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
            if (pos == count)
                break;
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    int n, k, t;
    int res;
    int stalks;

    pos = count = 0;
    n = getnum ();
    
    while (n--) {
        k = getnum ();
        stalks = 1;
        res = 1;

        while (k--) {
            t = getnum ();
#if DEBUG
            printf ("%d (%d) -> ", stalks, t);
#endif
            stalks = next (stalks, t);
#if DEBUG
            printf ("%d\n", stalks);
#endif
            if (stalks < 0)
                break;
        }

        if (stalks != 0)
            res = 0;

        puts (res ? "Yes" : "No");
    }
    return 0;
}
