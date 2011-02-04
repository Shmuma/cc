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


def divide (n, m):
    """
    Generates all decreasing sequences of length m sum of which are n:
    {4,0,0},{3,1,0},{2,1,1},{2,2,0}
    """
    res = []
    v = [n] + [0]*(m-1)
    res.append (v)
    
    return res


def fun (n, k, p, i):
    if k == 2:
        return binomial (n, i) % p


def res (n, k, p):
    res = 0
    for i in range (n+1):
        res += fun (n, k, p, i)
    return res
