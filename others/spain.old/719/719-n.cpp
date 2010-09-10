// 1. 0:04.44
// 2. 0:02.81
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

using namespace std;


char buf[20000];
int len;

int solve ();
int compare (int a, int b);


int main ()
{
    int n;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%s", buf);
        len = strlen (buf);

        printf ("%d\n", solve ()+1);
    }

    return 0;
}



int solve ()
{
    int ofs = 1, cmp, best_ofs = 0;
    int prev = -1;

    while (ofs) {
        cmp = compare (best_ofs, ofs);

        // when our string consists only from one letter
        //         if (!cmp)
        //             return 0;

        if (cmp <= 0) {
            while (buf[ofs] == buf[best_ofs]) {
                ofs++;
                ofs %= len;
                if (!ofs)
                    return best_ofs;
            }
        } else 
            best_ofs = ofs;
        
        prev = cmp;

        ofs++;
        ofs %= len;
    }

    return best_ofs;
}



int compare (int a, int b)
{
    for (int i = 0; i < len; i++) {
        if (buf[a] < buf[b])
            return -1;
        if (buf[a] > buf[b])
            return 1;
        
        a++;
        b++;
        a %= len;
        b %= len;
    }

    return 0;
}
