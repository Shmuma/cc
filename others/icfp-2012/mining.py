# 96530650

import sys
import logging
import heapq

from lib.world import World, dist
from lib.planner import make_plan


w_init = World ()
w_init.parse (sys.stdin.readlines ())
w_init.show_full ()

w = w_init.clone ()
goals = [(dist (l, w.robot), l) for l in w.lambdas]
plan, w2 = make_plan (w)

#plan = "LDRDDUULLLDDL"
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
