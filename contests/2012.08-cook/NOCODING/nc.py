import sys

def code (c):
    return ord (c) - ord ('a')


def check (s):
    limit = len (s) * 11
#    print limit
    v = code (s[0])
    count = 2
    for c in s[1:]:
#        print c, v, chr (v+ord ('a')), count
        count += 1
        cd = code (c)
        if cd < v:
            count += 26 - v
            v = 0
        count += cd - v
        v = cd
#        print count
        if count > limit:
            return False
    return count <= limit



t = int (sys.stdin.readline ())
for i in range (t):
    s = sys.stdin.readline ().strip ()
    if check (s):
        print "YES"
    else:
        print "NO"
