import sys
import bisect


# cache lookup_middelta
# merge it's requests for x and x+1

def lookup_middelta (cache, ints, p):
    v = cache.get (p, None)
    if v != None:
        return v
#    print "lookup: %s" % str (p)
    idx = bisect.bisect_right (ints, (p,))
    d = 0
    for i in ints[idx-1:]:
        if i[0] >= p:
            break
        if i[1] <= p:
            continue
        d += i[2]
#    print "delta: %d" % d
    cache[p] = d
    return d


def solve (ints, n):
    pts = {1: 1, n: n}
    middelta_cache = {}

    ints.sort ()

    for i in ints:
#        print i
        f, t, d = i

        # f
        md = lookup_middelta (middelta_cache, ints, f)
        v = pts.get (f, f)
        pts[f] = v + d + md
        # t
        md = lookup_middelta (middelta_cache, ints, t)
        v = pts.get (t, t)
        pts[t] = v + d + md
        # f-1
        md = lookup_middelta (middelta_cache, ints, f-1)
        if md != 0:
            v = pts.get (f-1, f-1)
            pts[f-1] = v + md
        # t+1
        md = lookup_middelta (middelta_cache, ints, t+1)
        if md != 0:
            v = pts.get (t+1, t+1)
            pts[t+1] = v + md

    mmin = n
    mmax = 0
    for v in pts.values ():
        mmin = min (mmin, v)
        mmax = max (mmax, v)

#    print mmin, mmax
    return mmin, mmax



for t in range (int (sys.stdin.readline ().strip ())):
    n, m = map (int, sys.stdin.readline ().strip ().split (' '))
    r = range (1, n+1)

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
