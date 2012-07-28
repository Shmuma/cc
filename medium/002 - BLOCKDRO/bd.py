import sys

class World (object):
    """
    World state
    """
    field = []
    pos = 0, 0
    height = 0

    def __init__ (self, field, pos, height = None):
        self.field = field
        self.pos = pos
        if height:
            self.height = height
        else:
            self.height = sum (map (sum, field))


    def show (self):
        """
        Display world's state
        """
        print "pos: %d, %d" % self.pos
        print "moves: %s" % self.valid_moves ()
        print "sum_h: %d" % self.height
        for l in self.field:
            print " ".join (map (str, l))
        print ""


    def valid_moves (self):
        """
        Return list of possible moves
        """
        res = ""
        x, y = self.pos
        sx, sy = len (self.field[0]), len (self.field)
        if x > 0 and self.field[y][x-1] > 0:
            res += "l"
        if x > 1 and self.field[y][x-2] > 0:
            res += "L"
        if y > 0 and self.field[y-1][x] > 0:
            res += "d"
        if y > 1 and self.field[y-2][x] > 0:
            res += "D"
        if x < sx-1 and self.field[y][x+1] > 0:
            res += "r"
        if x < sx-2 and self.field[y][x+2] > 0:
            res += "R"
        if y < sy-1 and self.field[y+1][x] > 0:
            res += "u"
        if y < sy-2 and self.field[y+2][x] > 0:
            res += "U"
        return res


    def move (self, dir):
        """
        Perform move and return resulting world.  Sanity of move haven't
        checked, so it must be one from returned by method valid_moves Move is
        char, one of 'uUdDrRlL'.
        """
        x, y = self.pos
        dx, dy = {'l': (-1,  0), 'L': (-2,  0),
                  'r': ( 1,  0), 'R': ( 2,  0),
                  'u': ( 0,  1), 'U': ( 0,  2),
                  'd': ( 0, -1), 'D': ( 0, -2)}[dir]
        field2 = [list (l) for l in self.field]
        field2[y][x] -= 1
        return World (field2, (x+dx, y+dy), self.height-1)


def solve (w, tgt):
#    w.show ()
    res = 0

    q = [w]
    while len (q) > 0:
        w = q.pop (0) 
#        if w.height == 2:
#        print "Pop"
#        w.show ()
        for c in w.valid_moves ():
            w2 = w.move (c)
#            print "Move: %s" % c
#            w2.show ()
            if w2.pos == tgt and w2.height == 1:
#                print "Path: %s" % hist
                res += 1
            q.append (w2)
    return res

def read_data ():
    return map (int, sys.stdin.readline ().strip ().split (" "))

t = int (sys.stdin.readline ().strip ())
for i in range (t):
    n, m = read_data ()
    sx, sy = read_data ()
    fx, fy = read_data ()
    field = [read_data () for r in range (n)]
#    field.reverse ()
    w = World (field, (sy-1, sx-1))
    print solve (w, (fy-1, fx-1))
