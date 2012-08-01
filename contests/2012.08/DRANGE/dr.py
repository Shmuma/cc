import sys

for t in range (int (sys.stdin.readline ().strip ())):
    n, m = map (int, sys.stdin.readline ().strip ().split (' '))
    r = range (1, n+1)
    for tt in range (m):
        w, x, y, z = map (int, sys.stdin.readline ().strip ().split (' '))
        if w == 2:
            w = -1
        w *= z
        for i in range (x-1, y):
            r[i] += w
    print max (r) - min (r)
