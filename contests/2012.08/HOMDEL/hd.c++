#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int graph[250][250];


int main ()
{
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int v = graph[i][k] + graph[k][j];
                if (graph[i][j] > v)
                    graph[i][j] = v;
            }
        }
    }

    int m;
    cin >> m;

    for (int t = 0; t < m; t++) {
        int src, gas, dest;
        cin >> src >> gas >> dest;
        int v1, v2;

        v1 = graph[src][gas] + graph[gas][dest];
        v2 = graph[src][dest];

        cout << v1 << " " << v1 - v2 << endl;
    }

    return 0;
}
