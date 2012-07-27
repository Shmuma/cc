import sys

T = int (sys.stdin.readline ())
for i in range (T):
    p = int (sys.stdin.readline ())
    res = 0
    while p > 2048:
        res += 1
        p -= 2048
    while p > 0:
        if p % 2 == 1:
            res += 1
        p /= 2
    print res
