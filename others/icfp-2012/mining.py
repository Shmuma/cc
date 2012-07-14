# 96530650

import sys
import logging

from lib.world import World
from lib.planner import make_plan


w = World ()
w.parse (sys.stdin.readlines ())
w.show_full ()

goal = w.lambdas[2]
print "Trying to reach lambda %s" % str (goal)

plan, score = make_plan (w, goal)

print "Got plan '%s' with score %d, verify" % (plan, score)

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
