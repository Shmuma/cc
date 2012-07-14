class World (object):
    """
    World state
    """
    
    # Robot position
    robot = None, None

    # lifts positions
    lifts = []

    # map characters
    map_lines = []

    # amount of lambdas
    lambdas = 0

    # maze size
    bounds = 0, 0

    ticks_passed = 0


    def __init__ (self, lines):
        """
        Create world from lines read from stdin
        """
        self.map_lines = []

        # preprocess lines, split it into parts
        for l in lines:
            self.map_lines.insert (0, list (l.strip ()))

        # process map data - locate robot, find lambdas, etc
        for i, l in enumerate (self.map_lines):
            # robot position
            try:
                pos = l.index ('R')
                self.robot = (i, pos)
            except:
                pass
            # lambda count
            self.lambdas += l.count ('\\')
            # lifts
            try:
                pos = l.index ('L')
                self.lifts.append ((pos, i))
            except:
                pass
            
        self.bounds = len (self.map_lines[0]), len (self.map_lines)


    def show_full (self):
        """
        Display full state
        """
        print "Tick: %d" % self.ticks_passed
        print "Robot: %d, %d" % self.robot
        print "Lambdas: %d" % self.lambdas
        print "Lifts: %s" % self.lifts
        self.show ()


    def show (self):
        """
        Display world state
        """
        for i in range (len (self.map_lines)):
            print "".join (self.map_lines[-(i+1)])
        print ""


    def in_bounds (self, x, y):
        if x < 0 or y < 0:
            return False
        if x >= self.bounds[0] or y >= self.bounds[1]:
            return False
        return True


    def get_cell (self, x, y):
        """
        Obtain cell's contents as char
        """
        return self.map_lines[y][x]


    def do_action (self, action):
        """
        Apply robot action to world. Return true if maze completed, false
        otherwise
        """
        deltas = {"L": (-1, 0), "R": (+1, 0), "U": (0, +1), "D": (0, -1)}
        if not action in deltas:
            return False
        dx, dy = deltas[action]
        x, y = self.robot
        nx, ny = x + dx, y + dy
        if not self.in_bounds (nx, ny):
            return False
        ch = self.get_cell (nx, ny)

        if ch in ' .\\O':
            # move is valid, update map
            self.map_lines[y][x] = ' '
            self.map_lines[ny][nx] = 'R'
            self.robot = nx, ny
            if ch == '\\':
                self.lambdas -= 1
            if ch == 'O':
                return True
        else:
            # check for rock move
            if action in "LR" and ch == "*":
                n2x = x + 2*dx
                if self.in_bounds (n2x, y) and self.get_cell (n2x, y) == ' ':
                    self.map_lines[y][n2x] = '*'
                    self.map_lines[y][x] = ' '
                    self.map_lines[y][nx] = 'R'
                    self.robot = nx, ny
        return False
                    

        
    def tick (self):
        """
        Update world's state according rules (fall boulder, etc)
        """
        # if lambdas counter reached zero, open all lifts
        if self.lambdas == 0:
            for x,y in self.lifts:
                self.map_lines[y][x] = 'O'
        pass
