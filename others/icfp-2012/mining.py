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
goals.sort ()
print goals
print len (goals)

for d, g in goals:
    plan, w2 = make_plan (w, g)
    if plan:
        w = w2
        score = w2.scores
    else:
        plan = "".join (w.history) + "A"
        score = w.scores

#plan = "LDRDDUULLLDDL"
print "Got plan '%s' with score %d, verify" % (plan, score)

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
