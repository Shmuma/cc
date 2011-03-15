#!/usr/bin/env python

import sys


def small (c):
    return c >= 'a' and c <= 'z'

def large (c):
    return c >= 'A' and c <= 'Z'

def check (q):
    return small (q[3]) and large (q[0]) and large (q[1]) and large (q[2]) and large (q[4]) and large (q[5]) and large (q[6])


r = ''
for l in sys.stdin:
    q = []
    for c in l:
        q.append (c)
        if len (q) < 7:
            continue
        if len (q) > 7:
            q = q[1:]

        if check (q):
            r += q[3]
            print q
#        s.append (q[3])

print r
