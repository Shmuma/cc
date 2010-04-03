#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <utility>

using namespace std;

int n, vol;
int dists[1000001];

typedef map< pair<int,int>, pair<int, int> > cache_t;

cache_t cache;


void solve (int pos, int rest, int* stops, int* vars)
{
    int a, b, d;
    int v1, v2;

    if (pos == n-1) {
        *stops = 0;
        *vars = 1;
        return;
    }
    cache_t::const_iterator it = cache.find (pair<int,int> (pos, rest));

    if (it != cache.end ()) {
        *stops = it->second.first;
        *vars = it->second.second;
        return;
    }

    d = dists[pos+1] - dists[pos];

    if (d <= rest) {
        solve (pos+1, rest - d, &a, &v1);
        solve (pos+1, vol - d, &b, &v2);

        b++;
        if (a > b) {
            v1 = v2;
            a = b;
        }
        else {
            if (a == b)
                v1++;
        }
    }
    else {
        solve (pos+1, vol - d, &a, &v1);
        a++;
    }

    *stops = a;
    *vars = v1;
    cache[pair<int,int> (pos, rest)] = pair<int, int> (a, v1);
}


int main(int argc, char *argv[])
{
    int i, stops, vars;

    scanf ("%d %d", &n, &vol);
    
    for (i = 0; i < n; i++)
        scanf ("%d", dists+i);

    solve (0, vol, &stops, &vars);
    printf ("%d %d\n", stops, vars);

    return 0;
}
