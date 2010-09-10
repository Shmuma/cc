#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

 
/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
template<typename T> vector<int> find_lis(vector<T> &a)
{
	vector<int> b, p(a.size());
	int u, v;
 
	if (a.size() < 1) return b;
 
	b.push_back(0);
 
	for (int i = 1; i < (int)a.size(); i++) {
		if (a[b.back()] < a[i]) {
			p[i] = b.back();
			b.push_back(i);
			continue;
		}
 
		for (u = 0, v = b.size()-1; u < v;) {
			int c = (u + v) / 2;
			if (a[b[c]] < a[i]) u=c+1; else v=c;
		}
 
		if (a[i] < a[b[u]]) {
			if (u > 0) p[i] = b[u-1];
			b[u] = i;
		}	
	}
 
	for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;
	return b;
}

int main ()
{
    vector<int> in, out;
    int v;
    vector<int>::const_iterator it;

    in.clear ();
    out.clear ();

    while (scanf ("%d", &v) == 1)
        in.push_back (v);

    out = find_lis (in);

    printf ("%d\n-\n", out.size ());
    it = out.begin ();

    while (it != out.end ()) {
        printf ("%d\n", in[*it]);
        it++;
    }

    return 0;
}
