import sys

t = int (sys.stdin.readline ().strip ())
for tt in range (t):
    n = int (sys.stdin.readline ().strip ())
    s = map (int, sys.stdin.readline ().strip ().split (' '))
    s.sort ()
    p = None
    diff = 10**10
    for i in range (len (s)):
        if p != None:
            diff = min (diff, abs (p - s[i]))
        p = s[i]
    print diff
