import sys

t = int (sys.stdin.readline ().strip ())
for tt in range (t):
    n = int (sys.stdin.readline ().strip ())
    s = sys.stdin.readline ().strip ()
    ss = list (s)
    for i, c in enumerate (s):
        if c == '1':
            if i > 0:
                ss[i-1] = 'X'
            if i < n-1:
                ss[i+1] = 'X'
            ss[i] = 'X'
#    print s
#    print "".join (ss)
    print ss.count ('0')
        
