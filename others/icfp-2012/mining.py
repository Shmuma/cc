# 96530650

import sys
import logging
import heapq
import threading
import signal

from lib.world import World, dist
from lib.planner import make_plan, planner_timeout
import lib.planner

debug = False
lib.planner.debug = debug

def int_handler (signal, frame):
    planner_timeout ()


signal.signal (signal.SIGINT, int_handler)

timer = threading.Timer (140, planner_timeout)
timer.start ()

try:
    w_init = World ()
    w_init.parse (sys.stdin.readlines ())
    if debug:
        w_init.show_full ()

    w = w_init.clone ()
    goals = [(dist (l, w.robot), l) for l in w.lambdas]
    plan, w2 = make_plan (w)

    print plan
except:
    pass

timer.cancel ()

#plan = "LDRDDUULLLDDL"
if debug:
    print "Got plan '%s' with score %d, verify" % (plan, w2.scores)

    w = w_init.clone ()
    for a in plan:
        print "Action '%s'" % a
        act_res = w.do_action (a)
        if act_res == None:
            print "Aborted!"
            break
        if act_res:
            print "Solved!"
            break
        if w.tick ():
            print "Destroyed!"
            w.show ()
            break
        w.show ()
    print "Scores: %d" % w.scores
