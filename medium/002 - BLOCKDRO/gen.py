import sys
import random

from solve import World

steps_min, steps_max = 25, 25

tests = 1
if len (sys.argv) == 2:
    tests = int (sys.argv[1])

def generate ():
    x, y = [random.randint (3, 8) for i in range (2)]
    fx, fy = [random.randint (1, i-1) for i in x, y]

    field = [[1 for i in range (x)] for j in range (y)]

    cx, cy = fx, fy
    field[fy][fx] += 1

    path = ""
    for s in range (random.randint (steps_min, steps_max)):
        w = World (field, (cx, cy))
        c = random.choice (w.valid_moves ())
        path += c
        w2 = w.move (c)
        cx, cy = w2.pos
        field[cy][cx] += 1

    sys.stderr.write (path+'\n')
    print y, x
    print cy+1, cx+1
    print fy+1, fx+1
    for l in field:
        print " ".join (map (lambda v: str (v-1), l))

print tests
for t in range (tests):
    generate ()
