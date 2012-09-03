import sys


def solve (n):
    res = 1
    for k in range (n):
        res += 2 ** int ((n - k) / 2)
#        res %= 1000000007
    return res


def solve2 (n):   
    p = int ((n-1)/2)
    res = ((2**(p)-1) << 1) % 1000000007
    if n % 2 == 1:
        res += (1 << (p+1)) % 1000000007
    else:
        res += (2 << (p+1)) % 1000000007
    return res


#v1 = [solve (n) for n in range (1, 10)]
#v2 = [solve2 (n) for n in range (1, 10)]
#print v1
#print v2
#exit (0)


#for i in range (10000):
#    v = (((2**i)-1) << 1) % 1000000007
#    s = "{0:b}".format (v)
#    print "%4d %s" % (i, s)
#sys.exit (1)

v = (2**2000) % 1000000007
print v 
vv = (2**1000) % 1000000007
print vv
print (vv*vv) % 1000000007
sys.exit (1)


t = int (sys.stdin.readline ().strip ())
for tt in range (t):
    n = int (sys.stdin.readline ().strip ())
    res = solve2 (n)
    print res
