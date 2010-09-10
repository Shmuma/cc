#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>

using namespace std;


int marb[20000];
int count;
map<int, bool> cache;


bool solve (int a, int b, int count);


int main ()
{
    int c = 1, i;
    int n;
    int m[10];

    while (1) {
        count = 0;
        for (i = 0; i < 6; i++) {
            scanf ("%d", &m[i+1]);
        }

        if (!m[6] && !m[1] && !m[2] && !m[3] && !m[4] && !m[5])
            break;

        // reducing marbles
        while (m[1] > 2) {
            m[1] -= 2;
            m[2] += 1;
        }

//         while (m[1] > 14) {
//             m[1] -= 10;
//             m[4] += 2;
//         }

        while (m[2] > 2) {
            m[2] -= 2;
            m[4] += 1;
        }

        while (m[3] > 2) {
            m[3] -= 2;
            m[6] += 1;
        }

        while (m[4] > 10) {
            m[4] -= 3;
            m[6] += 2;
        }

        while (m[5] > 20) {
            m[5] -= 6;
            m[6] += 5;
        }

        while (m[6] > 20)
            m[6] -= 2;

//         for (i = 1; i <= 6; i++)
//             printf ("%d ", m[i]);
//         printf ("\n");

        for (i = 1; i <= 6; i++) {
            for (int j = 0; j < m[i]; j++)
                marb[count++] = i;
        }

        cache.clear ();

        printf ("Collection #%d:\n", c++);
        if (solve (0, 0, count))
            printf ("Can be divided.\n");
        else
            printf ("Can't be divided.\n");
        //        printf ("Cache %d\n", cache.size ());
        printf ("\n");
    }

    return 0;
}


bool solve (int a, int b, int cnt)
{
    int key = (cnt << 16) | abs (a-b);

    if (!cnt) {
        //        printf ("Got %d and %d\n", a, b);
        cache[key] = a == b;
        return a == b;
    }

    map<int, bool>::const_iterator it = cache.find (key);

    if (it != cache.end ())
        return it->second;

    if (solve (a+marb[count-cnt], b, cnt-1)) {
        cache[key] = true;
        return true;
    }

    if (solve (a, b+marb[count-cnt], cnt-1)) {
        cache[key] = true;
        return true;
    }

    cache[key] = false;
    return false;
}
