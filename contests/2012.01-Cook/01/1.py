import sys
import re


def read_obj ():
    s = sys.stdin.readline ().strip ()
    v = re.split ('\s+', s)
    return (int (v[0]), int (v[1]), v[2])


def move (a, t):
    if a[2] == 'R':
        return (a[0] + t, a[1], a[2])
    if a[2] == 'L':
        return (a[0] - t, a[1], a[2])
    if a[2] == 'U':
        return (a[0], a[1] + t, a[2])
    if a[2] == 'D':
        return (a[0], a[1] - t, a[2])


def check_first (a, b, d):
    aa = move (a, d)
    bb = move (b, d)
    if aa[0] == bb[0] and aa[1] == bb[1]:
        return True
    return False


def check_second (idx, a, b, max_dir, min_dir):
    if a[idx] > b[idx] and a[2] == max_dir and b[2] == min_dir:
        return True
    if a[idx] < b[idx] and a[2] == min_dir and b[2] == max_dir:
        return True
    return False


def find_coll (a, b):
    dx = abs (a[0] - b[0])
    dy = abs (a[1] - b[1])
    if dx == dy and check_first (a, b, dx):
        return dx
    if a[0] == b[0] and check_first (a, b, float (dy) / 2):
        return float (dy) / 2
    if a[1] == b[1] and check_first (a, b, float (dx) / 2):
        return float (dx) / 2
    return None


t = int (sys.stdin.readline ())
for test in range (t):
    earth = read_obj ()
    n = int (sys.stdin.readline ())
    res = None
    for i in range (n):
       ast = read_obj ()
       coll = find_coll (earth, ast)
       if coll:
           if res:
               res = min (res, coll)
           else:
               res = coll
    if res:
        print "%.1f" % res
    else:
        print "SAFE"
