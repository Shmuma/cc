import sys
import re

t = int (sys.stdin.readline ().strip ())

for a in range (t):
    n = int (sys.stdin.readline ())
    vals = map (int, re.split ('\s+', sys.stdin.readline ().strip ()))
    h = {}
    ih = {}
    for v in vals:
        c = h.get (v, 0) + 1
        h[v] = c
        if c in ih:
            ih[c] = min (v, ih[c])
        else:
            ih[c] = v
    c = max (ih.keys ())
    v = ih[c]
    print "%d %d" % (v, c)
