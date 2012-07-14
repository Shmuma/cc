import heapq

from world import dist


def heur (world, goal):
    """
    Heruistic function for A*. Calculate manhatten distance between robot and goal
    """
    return dist (goal, world.robot)


def heap_entry (world, goal):
    """
    Make a heap entry
    """
    return (heur (world, goal) + len (world.history), world)


def make_plan (world, goal):
    """
    Builds a plan to reach a goal point with best score.
    Returns pair with plan string and world state.
    """
    # each entry in the heap is a pair of:
    # - sum of count of steps performed and heruistic
    # - world
    heap = []
    heapq.heappush (heap, heap_entry (world, goal))
    while len (heap) > 0:
        prio, w = heapq.heappop (heap)
        # check that goal reached
        if w.robot == goal:
            return "".join (w.history), w
        # not there yet - trying to move somewhere
        for a in "UDLR":
            w2 = w.clone ()
            w2.do_action (a)
            if w2.robot != w.robot:
                # if we moved somewere
                if not w2.tick ():
                    # robot not destroyed - good
                    entry = heap_entry (w2, goal)
                    heapq.heappush (heap, entry)
        # TODO: check that world is unstable and try to wait
    # no way to reach for a goal
    return None, None

