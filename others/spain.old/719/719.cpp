// 1. 0:04.44
// 2. 0:02.81

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

using namespace std;


char buf[20000];
int pos[20000];
int stat[20000];
int len;
char t[20000], y[20000];
map<int, string> cache;

int solve ();
void sort (int from, int to);
int compare (int a, int b);


int main ()
{
    int n;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%s", buf);
        len = strlen (buf);

        printf ("%d\n", solve ());

//         for (int i = 0; i < len; i++)
//             printf ("%d\n", stat[i]);
//         printf ("\n");
        memset (stat, 0, sizeof (stat));
    }

    return 0;
}


int solve ()
{
    for (int i = 0; i < len; i++)
        pos[i] = i;

    sort (0, len-1);
    
    return pos[0]+1;
}


void sort (int from, int to)
{
    int a = from, b = to, t;
    bool s = false;

    while (a < b) {
        if (compare (a, b) > 0) {
            t = pos[a];
            pos[a] = pos[b];
            pos[b] = t;
            s = !s;
        }

        if (s)
            b--;
        else
            a++;
    }

    if (a > from)
        sort (from, a-1);
    if (b < to)
        sort (b+1, to);
}


int compare (int a, int b)
{
    int aa = pos[a], bb = pos[b];
    int m = aa, res;

    if (bb > m)
        m = bb;

    // trying to memcmp first
    res = memcmp (buf+aa, buf+bb, len-m);

    if (!res) {
        const string *sa, *sb;
        map<int, string>::const_iterator it;

        it = cache.find (aa);
        if (it == cache.end ()) {
            memcpy (t, buf+aa, len-aa);
            memcpy (t+len-aa, buf, aa);
            t[len] = 0;
            cache[aa] = string (t);
            sa = &cache[aa];
        }
        else
            sa = &(it->second);

        it = cache.find (bb);
        if (it == cache.end ()) {
            memcpy (t, buf+bb, len-bb);
            memcpy (t+len-bb, buf, bb);
            t[len] = 0;
            cache[bb] = string (t);
            sb = &cache[bb];
        }
        else
            sb = &(it->second);

        res = strcmp (sa->c_str (), sb->c_str ());
    }

    return res;
}
