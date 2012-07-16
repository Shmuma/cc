import heapq

from world import dist


stop_planner = False
debug = False

def heur (world):
    """
    Heruistic function for A*.
    - lambdas remaining * 50
    - exit distance * 10
    - steps performed
    """
    res = len (world.history)
    res += len (world.lambdas) * 50
    if len (world.lambdas) > 0:
        res += min (map (lambda lam: dist (world.robot, lam), world.lambdas)) * 5
    res += min (map (lambda lift: dist (world.robot, lift), world.lifts))
    
    return res


def heap_entry (world):
    """
    Make a heap entry
    """
    return (heur (world), world)


def make_plan (world):
    """
    Builds a plan to reach a goal point with best score.
    Returns pair with plan string and world state.
    """
    # each entry in the heap is a pair of:
    # - sum of count of steps performed and heruistic
    # - world
    global stop_planner
    heap = []
    best_world = None
    best_plan = None
    heapq.heappush (heap, heap_entry (world))
    stop_planner = False
    while len (heap) > 0 and not stop_planner:
        prio, w = heapq.heappop (heap)
        # not there yet - trying to move somewhere
        for a in "UDLR":
            # sanity check move
            if w.action_possible (a):
                w2 = w.clone ()
                if w2.do_action (a) == True:
                    return "".join (w2.history), w2
#                if debug:
#                    print "".join (w2.history)
                if w2.robot != w.robot:
                    # if we moved somewere
                    if not w2.tick ():
                        # robot not destroyed - good
                        entry = heap_entry (w2)
                        heapq.heappush (heap, entry)
                        if not best_world or w2.scores > best_world.scores:
                            best_world = w2
                            best_plan = "".join (best_world.history)
                            if debug:
                                print "Best world updated. Scores %d, plan %s" % (best_world.scores, best_plan)
        # TODO: check that world is unstable and try to wait
    # no way to reach for a goal, TODO: need to track best world state (with max score and return it's history
    return best_plan+"A", best_world



def planner_timeout ():
    """
    Routine callen from different thread context when time limit is about to
    expire
    """
    global stop_planner
    if debug:
        print "Timeout, fall from planner"
    stop_planner = True
    
