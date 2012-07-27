import sys

cache = {1 : 1, 0: 0}

def solve (n):
    global cache

    if n in cache:
        return cache[n]
    
    res = max (n, solve (int (n / 2)) + solve (int (n / 3)) + solve (int (n / 4)))
    cache[n] = res
    return res



for l in sys.stdin:
    n = int (l.strip())
    print solve (n)

