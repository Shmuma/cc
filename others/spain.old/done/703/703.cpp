#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>


using namespace std;


int a[100][100];
int b[100][100];
int c[100][100];


static int compar_one (const void* a, const void* b)
{
    int aa, bb;

    aa = *(int*)a;
    bb = *(int*)b;

    return aa-bb;
}



class Sol
{
private:
    int _kind;
    int _d[3];

public:
    Sol (int kind, int a, int b, int c)
        : _kind (kind)
    {
        _d[0] = a; _d[1] = b; _d[2] = c;
    };

    const bool operator== (const Sol& a) const;

    void print ()
    {
        int min;

        if (_kind == 1)
            qsort ((void*)&_d, sizeof (_d)/sizeof (_d[0]), sizeof (_d[0]), &compar_one);
        if (_kind == 2) {
            while (!incr () && !decr ())
                rotate ();
        }

        printf ("%d %d %d\n", _d[0]+1, _d[1]+1, _d[2]+1);
    }

    bool exists (vector<Sol>& v);

    const bool incr () const
    { return _d[0] > _d[1] && _d[1] > _d[2]; };

    const bool decr () const
    { return _d[0] < _d[1] && _d[1] < _d[2]; };

    void rotate ()
    { 
        int t; 
        t = _d[2];
        _d[2] = _d[1];
        _d[1] = _d[0];
        _d[0] = t;
    }
};


vector<Sol> res;



int main ()
{
    int n, i, j, k;

    while (!feof (stdin)) {
        if (!scanf ("%d", &n))
            break;

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf ("%d", &a[i][j]);

        memset (&b, 0, sizeof (b));
        memset (&c, 0, sizeof (c));

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;

                for (k = 0; k < n; k++) {
                    if (k == i || k == j)
                        continue;

                    if (!a[i][j] && !a[j][i] && 
                        !a[j][k] && !a[k][j]) {
                        b[i][k] = 1; // transitive draw
                        c[i][k] = j;
                    }
                    if (a[i][j] && a[j][k]) {
                        b[i][k] = 2; // transitive win (c[i,k] holds j)
                        c[i][k] = j;
                    }
                }
            }
        
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                if (b[i][j] == 1 && !a[j][i] && !a[i][j]) {
                    Sol s (1, i, c[i][j], j);
                    if (!s.exists (res))
                        res.push_back (s);
                }
                if (b[i][j] == 2 && !a[i][j]) {
                    Sol s (2, i, c[i][j], j);
                    if (!s.exists (res))
                        res.push_back (s);
                }
            }

        printf ("%d\n", res.size ());

        vector<Sol>::iterator it = res.begin ();

        while (it != res.end ()) {
            it->print ();
            it++;
        }

        res.clear ();
    }

    return 0;
}



bool Sol::exists (vector<Sol>& v)
{
    vector<Sol>::const_iterator it = v.begin ();

    while (it != v.end ()) {
        if (*it == *this)
            return true;
        it++;
    }

    return false;
}


const bool Sol::operator== (const Sol& a) const
{
    if ((a._d[0] == _d[0] || a._d[0] == _d[1] || a._d[0] == _d[2]) &&
        (a._d[1] == _d[0] || a._d[1] == _d[1] || a._d[1] == _d[2]) &&
        (a._d[2] == _d[0] || a._d[2] == _d[1] || a._d[2] == _d[2])) 
        return true;

    return false;
}

