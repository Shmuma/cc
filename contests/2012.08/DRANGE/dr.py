import sys


def simplify_ints (ints, n):
    pos = 1
    for i_idx, i in enumerate (ints):
        f, t, d = i
        while pos < i[1]:
            if f < pos:
                f = pos
            elif f > pos:
                yield (pos, f, 0)
                pos = f
            flag = False
            for j in ints[i_idx+1:]:
                ff, tt, dd = j
                if ff > pos:
                    yield (pos, ff, d)
                    pos = ff
                    flag = True
                    break
                else:
                    t = min (t, tt)
                    d += dd
            if not flag:
                yield (pos, t, d)
                pos = t+1
    if pos <= n:
        yield (pos, n, 0)


def solve (ints, n):
    ints.sort ()
#    print ints
    mmin, mmax = n, 0
    for i in simplify_ints (ints, n):
        f, t, d = i
        mmin = min (mmin, f+d)
        mmax = max (mmax, t+d)
#        print i
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
