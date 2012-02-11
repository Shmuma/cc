import sys

min_sol = 0

def is_lucky (v):
    return all ((d == 4 or d == 7 for d in v))


def increment (v):
    i = len (v) - 1
    d = 1
    res = list (v)
    while d and i >= 0:
        n = res[i] + d
        res[i] = n % 10
        d = int (n / 10)
        i -= 1
    if i < 0:
        res = [d] + res
    return res
    


def solve (v, count):
    global min_sol
#    print "%d, %d: %s" % (min_sol, count, v)
    if count >= min_sol:
        return
    if is_lucky (v):
        min_sol = count
        return
    # increment
#    print "inc"
    solve (increment (v), count + 1)
    # replace
#    print v
    for pos in range (len (v)):
        for val in [3, 4, 6, 7]:           
            if v[pos] == val:
                continue
            tv = list (v)
            tv[pos] = val
#            print "Replace %d with %d at %d" % (v[pos], val, pos)
            solve (tv, count + 1)
    # prepend
    for val in range (1, 10):
        solve ([val] + v, count + 1)


t = int (sys.stdin.readline ())
for i in range (t):
    num = sys.stdin.readline ().strip ()
    min_sol = len (num)
    solve (map (int, list (num)), 0)
    print min_sol
