import sys
import bisect


# cache lookup_middelta
# merge it's requests for x and x+1

def lookup_middelta (cache, ints, p):
    """
    Returns pair of deltas for point p and p+1
    """
    v = cache.get (p, None)
    if v != None:
        return v
    # invalid - we must find first int with end > p
    idx = bisect.bisect_right (ints, (p,))
    d1, d2 = 0, 0
    for i in ints[idx-1:]:
        f, t, d = i
        if f >= p+1:
            break
        if t <= p:
            continue
        if p > f and t > p+1:
            d1 += d
            d2 += d
        elif f == p and t > p+1:
            d2 += d
        elif f < p and t == p+1:
            d1 += d
    cache[p] = d1, d2
    return d1, d2


def solve (ints, n):
    pts = {1: 1, n: n}
    middelta_cache = {}

    ints.sort ()

    for i in ints:
#        print i
        f, t, d = i

        md_fm, md_f = lookup_middelta (middelta_cache, ints, f-1)
        # f
        v = pts.get (f, f)
        pts[f] = v + d + md_f
        # f-1
        if md_fm != 0:
            v = pts.get (f-1, f-1)
            pts[f-1] = v + md_fm

        md_t, md_tp = lookup_middelta (middelta_cache, ints, t)
        # t
        v = pts.get (t, t)
        pts[t] = v + d + md_t
        # t+1
        if md_tp != 0:
            v = pts.get (t+1, t+1)
            pts[t+1] = v + md_tp

    mmin = n
    mmax = 0
    for v in pts.values ():
        mmin = min (mmin, v)
        mmax = max (mmax, v)

#    print mmin, mmax
    return mmin, mmax



for t in range (int (sys.stdin.readline ().strip ())):
    n, m = map (int, sys.stdin.readline ().strip ().split (' '))

    # intervals (from, to, delta)
    ints = []

    for tt in range (m):
        w, x, y, z = map (int, sys.stdin.readline ().strip ().split (' '))
        if w == 2:
            w = -1
        w *= z
        ints.append ((x, y, w))
    mmin, mmax = solve (ints, n)
    print mmax - mmin
