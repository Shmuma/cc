class World (object):
    """
    World state
    """
    
    # Robot position
    robot = None, None

    # lifts positions
    lifts = []

    # remaining lambdas positions
    lambdas = []

    # map characters
    map_lines = []

    # amount of lambdas
    init_lambdas_count = 0

    # maze size
    bounds = 0, 0

    ticks_passed = 0
    scores = 0

    # history of commands
    history = []


    def parse (self, lines):
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
                self.robot = (pos, i)
            except:
                pass
            # lambdas
            self.lambdas += [(j, i) for j, c in enumerate (l) if c == '\\']

            # lifts
            try:
                pos = l.index ('L')
                self.lifts.append ((pos, i))
            except:
                pass
        self.init_lambdas_count = len (self.lambdas)
        self.bounds = len (self.map_lines[0]), len (self.map_lines)       


    def clone (self):
        """
        Clone the world state
        """
        w = World ()
        w.robot = self.robot
        w.lifts = list (self.lifts)
        w.lambdas = list (self.lambdas)
        w.map_lines = [list (l) for l in self.map_lines]
        w.init_lambdas_count = self.init_lambdas_count
        w.bounds = self.bounds
        w.ticks_passed = self.ticks_passed
        w.scores = self.scores
        w.history = list (self.history)
        return w


    def show_full (self):
        """
        Display full state
        """
        print "Tick: %d" % self.ticks_passed
        print "Robot: %d, %d" % self.robot
        print "Lambdas: %s" % self.lambdas
        print "Lifts: %s" % self.lifts
        print "Scores: %d" % self.scores
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
        Apply robot action to world. Return None if abort performed, true if maze completed, false
        otherwise
        """
        self.history.append (action)
        if action == 'A':
            self.scores += (self.init_lambdas_count - len (self.lambdas)) * 25
            return None
        self.scores -= 1
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
                self.scores += 25
                self.lambdas.remove ((nx, ny))
            if ch == 'O':
                self.scores += self.init_lambdas_count * 50
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
        Returns True if robot was destroyed by rock, False otherwise
        """
        # if lambdas counter reached zero, open all lifts
        if len (self.lambdas) == 0:
            for x,y in self.lifts:
                self.map_lines[y][x] = 'O'

        # rocks fall (inefficient), don't process first line
        # we save falling rocks into list (rock coords, new_coord) to fulfill simulatenous update
        fall_list = []
        for y in range (1, self.bounds[1]):
            for x in range (self.bounds[0]):
                if self.get_cell (x, y) == '*':
                    # empty space
                    dn_cell = self.get_cell (x, y-1)
                    if dn_cell == ' ':
                        fall_list.append ([(x, y), (x, y-1)])
                        continue
                    # fall left or right
                    if dn_cell == '*':
                        if self.in_bounds (x+1, y):
                            if self.get_cell (x+1, y) == ' ' and self.get_cell (x+1, y-1) == ' ':
                                fall_list.append ([(x, y), (x+1, y-1)])
                                continue
                        if self.in_bounds (x-1, y):
                            if self.get_cell (x-1, y) == ' ' and self.get_cell (x-1, y-1) == ' ':
                                fall_list.append ([(x, y), (x-1, y-1)])
                                continue
                    if dn_cell == '\\':
                        if self.in_bounds (x+1, y):
                            if self.get_cell (x+1, y) == ' ' and self.get_cell (x+1, y-1) == ' ':
                                fall_list.append ([(x, y), (x+1, y-1)])
                                continue
        destroyed = False
        for s, d in fall_list:
#            print "%s -> %s" % (s, d)
            self.map_lines[s[1]][s[0]] = ' '
            self.map_lines[d[1]][d[0]] = '*'
            # check for robot destruction
            if self.robot == (d[0], d[1]-1):
                destroyed = True
        return destroyed


def dist (a, b):
    """
    Return Manhattan distance between two points
    """
    return abs (a[0] - b[0]) + abs (a[1] - b[1])
    
