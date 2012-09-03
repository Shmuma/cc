import sys

cache = {}


def two_pow_mod (p):
    global cache
    if p in cache:
        return cache[p]
    m = 1000000007
    if p < 32:
        res = (1 << p) % m
        cache[p] = res
        return res
    k = int (p / 2)
    v1 = two_pow_mod (k)
    if k == p-k:
        res = (v1*v1) % m
        cache[p] = res
        return res
    v2 = two_pow_mod (p-k)
    res = (v1*v2) % m
    cache[p] = res
    return res




def solve (n):
    res = 1
    for k in range (n):
        res += 2 ** int ((n - k) / 2)
#        res %= 1000000007
    return res


def solve2 (n):   
    p = int ((n-1)/2)
    v = two_pow_mod (p)
    res = ((v-1) << 1) % 1000000007
    if n % 2 == 1:
        res += (v << 1) % 1000000007
    else:
        res += (v << 2) % 1000000007
    return res


t = int (sys.stdin.readline ().strip ())
for tt in range (t):
    n = int (sys.stdin.readline ().strip ())
    res = solve2 (n)
    print res
