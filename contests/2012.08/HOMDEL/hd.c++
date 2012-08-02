#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> edge_t;
typedef multimap<int, edge_t > graph_t;
typedef map<int, int> dist_t;
typedef multimap<int, int> front_t;
typedef set<int> done_t;


void dijkstra (const graph_t& g, int src, dist_t& dist, done_t& needed)
{
    done_t done;
    front_t front;
    graph_t::const_iterator it;

    done.insert (src);
    it = g.find (src);
//    cout << src << endl;
    while (it != g.end ()) {
        if ((*it).first != src)
            break;
//        cout << (*it).first << ": " << (*it).second.first << ", " << (*it).second.second << endl;
        front.insert (edge_t ((*it).second.second, (*it).second.first));
        it++;
    }

    while (front.size () > 0) {
        int w, n;
        front_t::iterator f_it = front.begin ();

        w = (*f_it).first;
        n = (*f_it).second;
        front.erase (f_it);
        if (done.count (n) > 0)
            continue;
        dist[n] = w;
        done.insert (n);
        needed.erase (n);
        if (needed.size () == 0)
            break;

        it = g.find (n);
        while (it != g.end ()) {
            if ((*it).first != n)
                break;
            int nn, ww;
            nn = (*it).second.first;
            ww = (*it).second.second;
            if (done.count (nn) == 0)
                front.insert (edge_t (ww+w, nn));
            it++;
        }
    }
}


void solve (const graph_t& g, int src, int gas, int dest, int& p1, int& p2)
{
    dist_t dist;
    int src_gas, gas_dest, src_dest;
    done_t needed;

    needed.insert (gas);
    needed.insert (dest);
    dijkstra (g, src, dist, needed);
    src_gas = dist[gas];
    src_dest = dist[dest];

    dist.clear ();
    needed.insert (dest);
    dijkstra (g, gas, dist, needed);
    gas_dest = dist[dest];

    p1 = src_gas + gas_dest;
    p2 = p1 - src_dest;
}


int main ()
{
    int n;
    graph_t g;

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v;
            cin >> v;
            if (i == j)
                continue;
            g.insert (pair <int, edge_t > (i, edge_t (j, v)));
        }
    }

    int m;
    cin >> m;

    for (int t = 0; t < m; t++) {
        int src, gas, dest;
        cin >> src >> gas >> dest;

        int p1, p2;
        solve (g, src, gas, dest, p1, p2);
        cout << p1 << " " << p2 << endl;
    }

    return 0;
}
