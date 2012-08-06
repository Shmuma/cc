#include <iostream>
#include <stdlib.h>
#include <strings.h>


using namespace std;


struct interval {
    int start;
    int end;
    int delta;
};

struct interval ints[10000];
struct interval ints_end[10000];
int ints_count;

int pts[1000000];
int pts_count;


int ints_compare (const void* a, const void* b)
{
    const struct interval *ia, *ib;

    ia = (const struct interval*)a;
    ib = (const struct interval*)b;

    if (ia->start != ib->start)
        return ia->start - ib->start;

    if (ia->end != ib->end)
        return ia->end - ib->end;

    return 0;
}


int ints_compare_end (const void* a, const void* b)
{
    const struct interval *ia, *ib;

    ia = (const struct interval*)a;
    ib = (const struct interval*)b;

    if (ia->end != ib->end)
        return ia->end - ib->end;

    if (ia->start != ib->start)
        return ia->start - ib->start;

    return 0;
}


int lookup (int pt)
{
    int f = 0, t = ints_count, m;

    while (f < t) {
        m = (f+t) >> 1;
        if (ints_end[m].end < pt)
            f = m+1;
        else
            t = m-1;
    }
    return m-1;
}



void lookup_middelta (int p, int& md_p, int& md_pp)
{
    int nearest = lookup (p);

    md_p = 0;
    md_pp = 0;

    if (nearest == -1)
        return;

    while (nearest < ints_count) {
        if (ints[nearest].start < p && ints[nearest].end > p) {
            md_p += ints[nearest].delta;
            if (ints[nearest].end > p+1)
                md_pp += ints[nearest].delta;
        }
        else{
            if (ints[nearest].start > p)
                break;
        }
        nearest++;
    }
}


int main ()
{
    int t, n, m;

    cin >> t;
    while (t--) {
        cin >> n >> m;
        ints_count = 0;
        pts_count = n;

        for (int i = 0; i < m; i++) {
            int w, x, y, z;

            cin >> w >> x >> y >> z;
            ints[ints_count].start = x;
            ints[ints_count].end = y;
            ints[ints_count].delta = (w == 1 ? z : -z);
            ints_end[ints_count].start = x;
            ints_end[ints_count].end = y;
            ints_end[ints_count].delta = (w == 1 ? z : -z);
            ints_count++;
        }

        qsort (ints, ints_count, sizeof (struct interval), ints_compare);
        qsort (ints_end, ints_count, sizeof (struct interval), ints_compare_end);

        for (int i = 0; i < pts_count; i++)
            pts[i] = i+1;

        for (int i = 0; i < ints_count; i++) {
            int md_p, md_pp;
            int f = ints[i].start, t = ints[i].end, d = ints[i].delta;

            lookup_middelta (f-1, md_p, md_pp);
            pts[f-1] += d + md_pp;
            pts[f-2] += md_p;

            lookup_middelta (t, md_p, md_pp);
            pts[t-1] += d + md_p;
            pts[t] += md_pp;
        }

        int mmin = n, mmax = 0;
        for (int i = 0; i < pts_count; i++) {
            if (mmin > pts[i])
                mmin = pts[i];
            if (mmax < pts[i])
                mmax = pts[i];
        }

        cout << mmax - mmin << endl;
    }

    return 0;
}
