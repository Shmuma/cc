n = 1000
res = 0


def valid (n, k):
#    print "valid: %d %d" % (n, k)
    t = 0
    s = set ([t])
    for i in range (n):
#        print t
        t += k+1
        t = t % n
        s.add (t)
#    print t
#    print s
    return s == set (range (n))


for k in range (1, (n-1) / 2):
    if valid (n, k):
        res += 1
#        print k

print res
