import sys
import time
import binascii

debug = True

class World (object):
    """
    World state
    """
    field = []
    pos = 0, 0
    height = 0
    _hash = None

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


    def is_finish (self, target):
        """
        Check that this is finishing state
        """
        return self.height == 1 and self.pos == target


    def hash (self):
        """
        Return hash of world state
        """
        if self._hash == None:
            self._hash = binascii.crc32 (str (self.field) + str (self.pos))
        return self._hash


class DFSNode (object):
    """
    Node used to keep state in iterative DFS
    """
    world = None
    count = 0
    moves = []
    
    def __init__ (self, world):
        self.world = world
        self.moves = list (world.valid_moves ())


def solve (w, tgt):
    res = 0
    cache = {}
    s = [DFSNode (w)]
    while len (s) > 0:
        node = s.pop () 
        if len (node.moves) > 0:
            # we have moves to do
            # return node in stack
            s.append (node)
            # do move
            c = node.moves.pop ()
            w2 = node.world.move (c)
            # if target reached - remember this, or push new node otherwise
            if w2.is_finish (tgt):
                node.count += 1
            else:
                # check in cache
                h = w2.hash ()
                if h in cache:
                    node.count += cache[h]
                else:
                    s.append (DFSNode (w2))
        else:
            # all moves finished, if we have parent (topmost node in stack), we
            # remember collected counter. If stack is empty, return counter - it
            # is the solution
            if len (s) > 0:
                s[-1].count += node.count
                # also, store in cache
                h = node.world.hash ()
                cache[h] = node.count
            else:
                res = node.count
    return res


def read_data ():
    return map (int, sys.stdin.readline ().strip ().split (" "))

if __name__ == "__main__":
    t = int (sys.stdin.readline ().strip ())
    s_start = time.time ()
    for i in range (t):
        t_start = time.time ()
        n, m = read_data ()
        sx, sy = read_data ()
        fx, fy = read_data ()
        field = [read_data () for r in range (n)]
#    field.reverse ()
        w = World (field, (sy-1, sx-1))
        print solve (w, (fy-1, fx-1))
        if debug:
            sys.stderr.write ("Solved %dx%d in %.5f seconds\n" % (n, m, time.time () - t_start))
    if debug:
        sys.stderr.write ("Suite solved in %.5f\n" % (time.time () - s_start))


# 1. test001: 8.64300
