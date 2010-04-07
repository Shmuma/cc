#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <utility>
#include <vector>


using namespace std;

int n, vol;
vector<int> dists;

typedef map<int, int> inner_t ;

map<int, inner_t> table;


void solve (int* stops, int* vars)
{
    int i, m;
    inner_t::iterator it;

    // build table
    printf ("%d: %d <- %d\n", n-1, 0, 0);
    table[n-1][0] = 0;
    for (i = n-2; i >= 0; i--) {
        it = table[i+1].begin ();

        while (it != table[i+1].end ()) {
            int d, c;

            d = it->first;
            c = it->second;

            d += dists[i];
            if (d > vol) {
                d -= vol;
                c++;
            }
            printf ("%d: %d <- %d\n", i, d, c);
            table[i][d] = c;
            it++;
        }
    }

    it = table[0].begin ();
    m = it->second;
    while (it != table[0].end ()) {
        if (it->second < m)
            m = it->second;
        it++;
    }

    *stops = m;
    *vars = 0;
}


int main(int argc, char *argv[])
{
    int i, stops, vars, v, vv;

    scanf ("%d %d", &n, &vol);
    scanf ("%d", &v);

    for (i = 1; i < n; i++) {
        scanf ("%d", &vv);
        dists.push_back (vv-v);
        v = vv;
    }

    solve (&stops, &vars);
    printf ("%d %d\n", stops, vars);

    return 0;
}
