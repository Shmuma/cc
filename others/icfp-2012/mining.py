import sys
import logging

from lib.world import World


def show_map (map_data):
    print "Robot: %d, %d" % map_data['robot']

    for i in range (len (map_data['map'])):
        print map_data['map'][-(i+1)]
    print ""


def move_robot (map_data, dx, dy):
    """
    Create new map according robot movement
    """
    x, y = map_data['robot']
    nx, ny = x + dx, y + dy


def next_map (map_data, action):
    """
    Calculates next map according to action applied. Action should be one of:
    - LRUD - move robot
    - W - wait
    """
    if action in "LRUD":
        # check action for validity
        dx, dy = {"L": (-1, 0), "R": (+1, 0), "U": (0, +1), "D": (0, -1)}[action]
        new_map_data = move_robot (map_data, dx, dy)
        if new_map_data == None:
            # move is invalid, ignore move request
            logging.info ("Action '%s' is invalid, ignore it" % action)
        else:
            map_data = new_map_data
    return map_data


# read map specification
#map_data = read_map ()
#show_map (map_data)


w = World (sys.stdin.readlines ())
w.show_full ()

for a in "DLLLDDRRRLLLL":
    print "Action '%s'" % a
    if w.do_action (a):
        print "Solved!"
        break
    w.tick ()
    w.show ()

