import sys

def read_data ():
    return map (int, sys.stdin.readline ().strip ().split (" "))

t = int (sys.stdin.readline ().strip ())
for i in range (t):
    n, m = read_data ()
    sx, sy = read_data ()
    fx, fy = read_data ()
    w = [read_data () for r in range (n)]
    print w
