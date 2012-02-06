import sys

def calc_dat (s):
    h = {}
    for l in s:
        if l in h:
            h[l] += 1
        else:
            h[l] = 1
    return h.values ()


def fact (n):
    res = 1
    while n > 0:
        res *= n
        n -= 1
    return res


def solve (dat):
    res = fact (sum (dat))
    for i in dat:
        if i > 1:
            res /= fact (i)
    return res % 1000000007


n = int (sys.stdin.readline ().strip ())

for i in range (n):
    s = sys.stdin.readline ().strip ()
    dat = calc_dat (s)
    print solve (dat)
