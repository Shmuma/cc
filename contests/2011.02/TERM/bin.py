#!/usr/bin/env python

from math import *

def binomial (n, k):
    return factorial (n) / factorial (k) / factorial (n-k)


def multinomial (l):
    """
    Calculate multinomial coeeficient using list of xi
    """
    r = factorial (sum (l))
    for v in l:
        r /= factorial (v)
    return r


def fun (n, k, p):
    if n < p:
        return binomial (n+k-1, n)
    lim = (n/p)*p
    res = 0
    for d in range (lim, n+1):
        t = n-d+1
        if t > k:
            continue
        v = binomial (k, k-t)*factorial (t)
        print t, v
        res += v
    return res


def res (n, k, p):
    res = 1
    for i in range (1, n+1):
        v = fun (i, k, p)
        res += v
        print "fun (%d, %d, %d) = %d" % (i, k, p, v)
    return res
